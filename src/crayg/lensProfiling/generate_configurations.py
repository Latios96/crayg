import itertools
import json
import os
from pathlib import Path

import yaml

TEMPLATE = {
    "serverUrl": "https://cato.frmbffr.com",
    "projectName": "Crayg Lens Profiling",
    "suites": [],
    "variables": {
        "crayg_render_command": 'C:\\workspace\\crayg\\cmake-build-relwithdebinfo\\bin/crayg-standalone -s {{scene_path}} -o "{{image_output_exr}}" --camera {{camera}} --integrator=RAYTRACING --intersector=EMBREE --maxSamples 16'
    },
    "command": "{{crayg_render_command}}",
    "comparisonSettings": {"method": "FLIP", "threshold": 0.25},
}


def get_camera_lens_types(camera):
    return ["realistic"]
    if camera["cameraTypes"] == "all":
        return ["thin_lens", "realistic"]
    return camera["cameraTypes"]


SCENE_FILE_TEMPLATE = """#usda 1.0
(
    subLayers = [
        @$BASE_SCENE_PATH$@
    ]
)

over "$CAMERA_NAME$" {
    custom string craygCameraType = "$CAMERA_TYPE$"
    custom string craygLensFile = "$LENS_FILE_PATH$"
}
"""

if __name__ == "__main__":
    with open(Path(__file__).parent / "config.yml", "r") as stream:
        scenes_data = yaml.safe_load(stream)
    suite_count = 0
    test_count = 0
    for scene in scenes_data["scenes"]:
        suite = {}
        TEMPLATE["suites"].append(suite)
        suite["name"] = scene["name"]
        suite["tests"] = []
        for camera in scene["cameras"]:
            for camera_type in get_camera_lens_types(camera):
                for i in range(3):
                    test_name = f"{i}-{os.path.basename(camera['name'])}-{camera_type}"
                    if camera_type == "realistic":
                        test_name += os.path.splitext(
                            os.path.basename(camera["lensFile"])
                        )[0]
                    print(test_name)

                    base_scene_path = scene["scenePath"]
                    target_file = os.path.join(
                        os.path.dirname(__file__),
                        scene["name"],
                        f"{os.path.basename(camera['name'])}-{camera_type}",
                        f"{os.path.basename(camera['name'])}-{camera_type}.usda",
                    )
                    target_folder = os.path.dirname(target_file)
                    if not os.path.exists(target_folder):
                        os.makedirs(target_folder)
                    content = (
                        SCENE_FILE_TEMPLATE.replace(
                            "$BASE_SCENE_PATH$", base_scene_path
                        )
                        .replace("$CAMERA_NAME$", camera["name"][1:])
                        .replace("$CAMERA_TYPE$", camera_type.upper())
                        .replace("$LENS_FILE_PATH$", camera["lensFile"])
                    )
                    with open(target_file, "w") as f:
                        f.write(content)

                    suite["tests"].append(
                        {
                            "name": test_name,
                            "variables": {
                                "scene_path": target_file,
                                "camera": camera["name"],
                            },
                        }
                    )
                    test_count += 1
        suite_count += 1
    with open("cato.json", "w") as f:
        json.dump(TEMPLATE, f, indent=4)

    print(f"Generated {suite_count} suites with {test_count} tests")
