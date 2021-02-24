import os
from pathlib import Path
from typing import Tuple

from mako.template import Template

from ..model import AutojailConfig, Board, CellConfig, JailhouseConfig
from ..utils.logging import getLogger
from .passes import BasePass

_root_template = Template(
    """

enable_${name}()
{
    modprobe jailhouse
    /usr/sbin/jailhouse enable ${cell_config} 
}

"""
)

_linux_template = Template(
    """

enable_root()
{
    /usr/sbin/jailhouse cell linux ${cell_config} ${kernel} ${dtb} -i ${cell_image} -c "console=ttyS0,115200 ${ip_config} ${nfsroot} ${flags}"
} 

"""
)

_bare_template = Template(
    """

enable_${name}()
{
    if ! $(jailhouse_enabled); then
        enable_root;
    fi
    jailhouse cell create ${cell_config}
    %if cell_image:
    /usr/sbin/jailhouse cell load --name "${cell_name}" ${cell_image}
    /usr/sbin/jailhouse cell start --name "${cell_name}"
    %endif
} 
"""
)

_all_template = Template(
    """
#!/bin/bash

jailhouse_enabled()
{
    if test -e  /sys/devices/jailhouse/enabled; then
        enabled = $(cat /sys/devices/jailhouse/enabled)
        return $enabled
    fi

    return 0
}

${enable_root}

%for cell in enable_cells:

${enable_cells[cell]}

%endfor

enable()
{
    if ! $(jailhouse_enabled); then
        enable_root;
    fi

%for cell_name in cell_names:
    enable_${cell_name};
%endfor
}


enable;

"""
)


class GenerateStartupPass(BasePass):
    def __init__(self, config: AutojailConfig):
        self.logger = getLogger()
        self.autojail_config = config

    def __call__(
        self, board: Board, config: JailhouseConfig
    ) -> Tuple[Board, JailhouseConfig]:

        self.board = board
        self.config = config

        root_startup = ""
        guest_startups = {}
        cell_names = []
        for cell_name, cell in config.cells.items():
            if cell.type == "root":
                root_startup = self._generate_root_startup(cell)
            else:
                guest_startups[cell_name] = self._generate_guest_startup(
                    cell_name, cell
                )
                cell_names.append(cell.name.lower().replace(" ", "_"))
        startup_code = _all_template.render(
            enable_root=root_startup,
            enable_cells=guest_startups,
            cell_names=cell_names,
        )

        deploy_path = Path(self.autojail_config.deploy_dir)
        target_path = deploy_path / "etc" / "jailhouse" / "enable.sh"
        with target_path.open("w") as f:
            f.write(startup_code)

        os.chmod(target_path, 0o755)

        return board, config

    def _generate_root_startup(self, cell: CellConfig):
        cell_name = cell.name.lower().replace(" ", "_")
        cell_config_name = cell_name + ".cell"
        cell_config_path = "/etc/jailhouse/" + cell_config_name
        return _root_template.render(
            name=cell_name, cell_config=cell_config_path
        )

    def _generate_guest_startup(self, cell_id: str, cell: CellConfig):
        cell_name = cell.name.lower().replace(" ", "_")
        cell_name_escaped = cell.name.lower().replace(" ", "-")
        cell_config_name = cell_name_escaped + ".cell"
        cell_config_path = "/etc/jailhouse/" + cell_config_name
        if cell.image:
            local_image_path = Path(cell.image)
            cell_image = "/usr/share/jailhouse/" + local_image_path.name
        else:
            cell_image = ""

        if cell.type == "linux":
            kernel = "/boot/vmlinuz-5.4.16"
            dtb = "/etc/jailhouse/dts/" + cell_name_escaped + ".cell"
            ip_config = ""

            interfaces = []
            for shmem_config in self.config.shmem.values():
                if cell_id in shmem_config.peers:
                    if shmem_config.network:
                        assert isinstance(shmem_config.network, dict)
                        interfaces.extend(
                            shmem_config.network[cell_id].addresses
                        )
            if len(interfaces) > 1:
                self.logger.critical(
                    f"Cell {cell.name} has more than one interface this can not be configured using kernel commandline"
                )
                self.logger.info(f"Choosing configuration {interfaces[0]}")

            if len(interfaces) > 0:
                interface = interfaces[0]
                ip_config = "ip={interface.ip}"

            nfsroot = ""
            flags = " ".join(["console=ttyS0,115200"])
            return _linux_template.render(
                name=cell_name,
                cell_name=cell.name,
                cell_config=cell_config_path,
                cell_image=cell_image,
                kernel=kernel,
                dtb=dtb,
                ip_config=ip_config,
                nfsroot=nfsroot,
                flags=flags,
            )
        else:
            return _bare_template.render(
                name=cell_name,
                cell_name=cell.name,
                cell_config=cell_config_path,
                cell_image=cell_image,
            )
