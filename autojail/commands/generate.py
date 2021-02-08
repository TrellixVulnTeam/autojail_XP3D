from pathlib import Path

import ruamel.yaml

from ..config import JailhouseConfigurator
from ..model import Board
from .base import BaseCommand


class GenerateCommand(BaseCommand):
    """Generate the Jailhouse configurations

    generate
        {--p|print-after-all : print cell config after each transformation step}
        {--skip-check : Do not statically check generated configs}
        {--target} : Deploy generated configs to target board
    """

    def handle(self) -> int:
        if not self.autojail_config:
            self.line(f"<error>could not find {self.CONFIG_NAME}</error>")
            return 1

        cells_yml_path = Path.cwd() / self.CELLS_CONFIG_NAME

        if not cells_yml_path.exists():
            self.line(f"<error>{cells_yml_path} could not be found</error>")
            return 1

        board_yml_path = Path.cwd() / self.BOARD_CONFIG_NAME
        if not board_yml_path.exists():
            self.line(f"<error>{board_yml_path} could not be found</error>")
            self.line("Please run <comment>automate extract</comment> first")
            return 1

        with board_yml_path.open() as f:
            yaml = ruamel.yaml.YAML()
            board_dict = yaml.load(f)
            board_info = Board(**board_dict)

        configurator = JailhouseConfigurator(
            board_info,
            self.autojail_config,
            print_after_all=self.option("print-after-all"),
            context=self.automate_context,
        )
        configurator.read_cell_yml(str(cells_yml_path))
        configurator.prepare()
        ret = configurator.write_config(self.autojail_config.build_dir)
        if ret:
            configurator.report()
            return ret

        ret = configurator.build_config(
            self.autojail_config.build_dir, skip_check=self.option("skip-check")
        )
        if ret:
            configurator.report()
            return ret

        ret = configurator.deploy(
            self.autojail_config.build_dir,
            self.autojail_config.deploy_dir,
            target=self.option("target"),
        )
        configurator.report()

        return ret
