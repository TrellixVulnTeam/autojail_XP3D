from pathlib import Path
from typing import Optional

import ruamel.yaml
from cleo import Command

from autojail.model.board import Board
from autojail.model.jailhouse import JailhouseConfig

from ..model import AutojailConfig

automate_available = False
try:
    import automate

    automate_available = True
except ImportError:
    automate_available = False


class BaseCommand(Command):
    CONFIG_NAME = "autojail.yml"
    CELLS_CONFIG_NAME = "cells.yml"
    BOARD_CONFIG_NAME = "board.yml"

    @property
    def cells_config_path(self):
        return Path.cwd() / self.CELLS_CONFIG_NAME

    @property
    def board_config_path(self):
        return Path.cwd() / self.BOARD_CONFIG_NAME

    def load_jailhouse_config(self) -> Optional[JailhouseConfig]:
        if not self.cells_config_path.exists():
            self.line(
                f"{self.cells_config_path} does not exist use autojail config init to generate root cell config"
            )
            return None

        with self.cells_config_path.open() as f:
            yaml = ruamel.yaml.YAML()
            cells_dict = yaml.load(f)
            cells_info = JailhouseConfig(**cells_dict)

        return cells_info

    def load_board_info(self) -> Optional[Board]:
        if not self.board_config_path.exists():
            self.line(
                f"<error>{self.board_config_path} could not be found</error>"
            )
            self.line("Please run <comment>automate extract</comment> first")
            return None

        with self.board_config_path.open() as f:
            yaml = ruamel.yaml.YAML()
            board_dict = yaml.load(f)
            board_info = Board(**board_dict)

        return board_info

    def __init__(self) -> None:
        super().__init__()

        self.autojail_config = None
        self.config_path = Path.cwd() / self.CONFIG_NAME
        if self.config_path.exists():
            with self.config_path.open() as f:
                yaml = ruamel.yaml.YAML()
                config_dict = yaml.load(f)
                self.autojail_config = AutojailConfig(**config_dict)

        self.automate_context = None
        if automate_available:
            automate_config = automate.AutomateConfig()
            self.automate_context = automate.AutomateContext(automate_config)
