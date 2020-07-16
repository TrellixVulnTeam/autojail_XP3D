import os

from cleo import CommandTester

from autojail.main import AutojailApp
from ruamel.yaml import YAML

project_folder = os.path.join(os.path.dirname(__file__), "..", "projects")


def test_init(tmpdir):
    os.chdir(tmpdir)
    application = AutojailApp()
    command = application.find("init")
    tester = CommandTester(command)

    yaml = YAML()

    tester.execute(interactive=False)
    assert os.path.exists(os.path.join(tmpdir, "autojail.yml"))
    with open("autojail.yml") as f:
        data1 = yaml.load(f)

    tester.execute(["-f"], interactive=False)
    assert os.path.exists(os.path.join(tmpdir, "autojail.yml"))
    with open("autojail.yml") as f:
        data2 = yaml.load(f)

    tester.execute(["-f"], interactive=True, inputs="\n\n\n\n\n\n\n\n\n")
    assert os.path.exists(os.path.join(tmpdir, "autojail.yml"))
    with open("autojail.yml") as f:
        data3 = yaml.load(f)

    assert data1["name"] == data2["name"] == data3["name"]
    assert data1["arch"] == data2["arch"] == data3["arch"]
    assert (
        data1["jailhouse_dir"]
        == data2["jailhouse_dir"]
        == data3["jailhouse_dir"]
    )
    assert (
        data1["cross_compile"]
        == data2["cross_compile"]
        == data3["cross_compile"]
    )

    tester.execute(
        "-f --arch arm --name jailhouse_test --uart /dev/ttyUSB0",
        interactive=False,
    )
    assert os.path.exists(os.path.join(tmpdir, "autojail.yml"))
    with open("autojail.yml") as f:
        data_test = yaml.load(f)

    assert data_test["name"] == "jailhouse_test"
    assert data_test["arch"] == "ARM"
    assert data_test["uart"] == "/dev/ttyUSB0"

    try:
        import automate  # noqa

        tester.execute("-f -a", interactive=False)
        assert os.path.exists(os.path.join(tmpdir, "autojail.yml"))
    except ModuleNotFoundError:
        pass


def test_simple(tmpdir):
    """tests a simple generation from cells.yml only"""
    os.chdir(tmpdir)
    application = AutojailApp()
    command = application.find("init")
    tester = CommandTester(command)
    tester.execute(interactive=False)

    command = application.find("config")
    tester = CommandTester(command)
    tester.execute(interactive=False)