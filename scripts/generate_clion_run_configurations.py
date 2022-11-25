import os
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path
from typing import Optional, List


@dataclass
class RunConfigParameter:
    scene_path: Path
    name_override: Optional[str] = None

    @property
    def name(self):
        prefix = "standalone-gui"
        if self.name_override:
            return f"{prefix} {self.name_override}"
        return f"{prefix} {os.path.splitext(self.scene_path.name)[0]}"


def generate_run_config(run_manager, config: RunConfigParameter):
    print(f"Creating {config.name}")
    configuration_element = ET.Element("configuration")
    configuration_element.set("name", config.name)
    configuration_element.set("type", "CMakeRunConfiguration")
    configuration_element.set("factoryName", "Application")
    configuration_element.set(
        "PROGRAM_PARAMS", f"-s {config.scene_path} -o usdPreviewSurfaceTest.#.png"
    )
    configuration_element.set("REDIRECT_INPUT", "false")
    configuration_element.set("ELEVATE", "false")
    configuration_element.set("USE_EXTERNAL_CONSOLE", "false")
    configuration_element.set("PASS_PARENT_ENVS_2", "true")
    configuration_element.set("PROJECT_NAME", "crayg")
    configuration_element.set("TARGET_NAME", "standalone-gui")
    configuration_element.set("CONFIG_NAME", "Release-Visual Studio")
    configuration_element.set("RUN_TARGET_PROJECT_NAME", "crayg")
    configuration_element.set("RUN_TARGET_NAME", "standalone-gui")
    configuration_element.set("generated_by_script", "true")
    method_element = ET.Element("method")
    method_element.set("v", "2")
    option_element = ET.Element("option")
    option_element.set(
        "name",
        "com.jetbrains.cidr.execution.CidrBuildBeforeRunTaskProvider$BuildBeforeRunTask",
    )
    option_element.set("enabled", "true")
    method_element.append(option_element)
    configuration_element.append(method_element)

    run_manager.append(configuration_element)

    configuration_list = run_manager.find("list")
    list_item = ET.Element("item")
    list_item.set("itemvalue", "CMake Application." + config.name)

    configuration_list.append(list_item)


def collect_integration_test_scenes():
    directory = (
            Path(os.path.abspath(__file__)).parent.parent
            / "src"
            / "crayg"
            / "integrationTests"
    )
    return [RunConfigParameter(x) for x in directory.glob("**/*.usda")]


def collect_test_scenes(scenes: List[RunConfigParameter]):
    if os.path.exists(r"M:\Test_Scene_Collection"):
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\ALab\entry.usda"),
                name_override="Animal Logic ALab",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Intel_Sponza\Default.usda"),
                name_override="Intel Sponza Main",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Intel_Sponza\WithCandles.usda"),
                name_override="Intel Sponza with Candles",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Intel_Sponza\WithCurtains.usda"),
                name_override="Intel Sponza with Curtains",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Intel_Sponza\WithIvy.usda"),
                name_override="Intel Sponza with Ivy",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Intel_Sponza\WithTrees.usda"),
                name_override="Intel Sponza with Trees",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\moana-island\usd\island.usda"),
                name_override="Moana Island",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Pixar_Kitchen_set\Kitchen_set.usd"),
                name_override="Pixar Kitchen",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Lego_Models\Hubble.usda"),
                name_override="Hubble",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Lego_Models\Space_Shuttle.usda"),
                name_override="Space Shuttle",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\Lego_Models\Millennium_Falcon.usda"),
                name_override="Millennium Falcon",
            )
        )
        scenes.append(
            RunConfigParameter(
                Path(r"M:\Test_Scene_Collection\ALab\entry_flattened.usd"),
                name_override="ALab",
            )
        )


def add_not_existing_run_configurations(run_manager, scenes):
    existing_configs = set()
    for ch in run_manager:
        existing_configs.add(ch.get("name"))
    for scene in scenes:
        if scene.name not in existing_configs:
            generate_run_config(run_manager, scene)


def get_run_manager_element(tree):
    root = tree.getroot()
    run_manager = root.find("component[@name='RunManager']")
    return run_manager


def main():
    scenes = collect_integration_test_scenes()
    collect_test_scenes(scenes)
    workspace_xml_path = (
            Path(os.path.abspath(__file__)).parent.parent / ".idea" / "workspace.xml"
    )
    tree = ET.parse(workspace_xml_path)
    run_manager = get_run_manager_element(tree)

    add_not_existing_run_configurations(run_manager, scenes)

    tree.write(workspace_xml_path)


if __name__ == "__main__":
    main()
