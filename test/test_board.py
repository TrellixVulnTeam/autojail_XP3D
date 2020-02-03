import os.path
import yaml

from autojail.model.board import Board


test_data_folder = os.path.join(os.path.dirname(__file__), "test_data")


def test_board():
    test_data = {
        "id": "test_id",
        "name": "test_name",
        "board": "test_board",
        "memory_regions": {
            "test_region": {
                "virtual_start_addr": 0x1000,
                "physical_start_addr": 0x1000,
                "size": 100,
                "flags": ["MEM_READ"],
            }
        },
    }

    board_model = Board(**test_data)

    assert board_model.id == "test_id"
    assert (
        board_model.memory_regions["test_region"].virtual_start_addr == 0x1000
    )
    assert (
        board_model.memory_regions["test_region"].physical_start_addr == 0x1000
    )
    assert board_model.memory_regions["test_region"].size == 100


def test_board_from_yaml():
    board_yaml = os.path.join(test_data_folder, "test_board.yml")
    with open(board_yaml) as board_yaml_file:
        board_dict = yaml.load(board_yaml_file)
        board_model = Board(**board_dict)

        assert board_model.id == "board1"
