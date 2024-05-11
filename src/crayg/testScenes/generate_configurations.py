import itertools
import json
import os
from pathlib import Path
from typing import Set, Optional, List
from pydantic import BaseModel

import typer
import yaml

TEMPLATE = {
    "serverUrl": "https://cato.frmbffr.com",
    "projectName": "Crayg Test Scenes",
    "suites": [],
    "variables": {
        "crayg_render_command": 'C:\\workspace\\crayg\\cmake-build-relwithdebinfo\\bin/crayg-standalone -s {{scene_path}} -o "{{image_output_exr}}" --camera {{camera}} --integrator={{integrator}} --intersector={{intersector}} --maxSamples {{maxSamples}} --resolution {{resolution}} {{useSpectralLensing}} {{selectedVariant}}'
    },
    "command": "{{crayg_render_command}}",
    "comparisonSettings": {"method": "FLIP", "threshold": 0.25},
}


class VariantSet(BaseModel):
    prim_path: str
    variant_set: str
    variants: List[str]


class Scene(BaseModel):
    name: str
    cameras: List[str]
    scene_path: str
    integrators: List[str]
    intersectors: List[str]
    hero_camera: Optional[str] = None
    resolution: Optional[str] = None
    variant_set: Optional[VariantSet] = None


def load_config() -> List[Scene]:
    with open(Path(__file__).parent / "config.yml", "r") as stream:
        scenes_data = yaml.safe_load(stream)
        return list(map(lambda scene: Scene(**scene), scenes_data["scenes"]))


def filter_string_list(strings: List[str], strings_to_keep: Set[str]) -> List[str]:
    result = []
    for s in strings:
        if s in strings_to_keep:
            result.append(s)
    return result


def remove_unselected_configurations(
    scenes: List[Scene],
    only_hero_cam: bool = False,
    integrators: Set[str] = None,
    scene_names: Set[str] = None,
) -> List[Scene]:
    filtered_scenes = []
    for scene in scenes:
        scene = scene.copy()
        if scene_names and scene.name not in scene_names:
            continue
        if only_hero_cam:
            if not scene.hero_camera:
                continue
            scene.cameras = [scene.hero_camera]
        if integrators:
            filtered_integrators = filter_string_list(scene.integrators, integrators)
            if not filtered_integrators:
                continue
            scene.integrators = filtered_integrators
        filtered_scenes.append(scene)

    return filtered_scenes


def resolve_resolution(scene: Scene, global_resolution: Optional[str]) -> str:
    if global_resolution:
        return global_resolution
    return scene.resolution if scene.resolution else "1280x720"


app = typer.Typer()


@app.command(help="Generate cato config for test scense")
def generate_config(
    only_hero_cam: bool = False,
    integrators: List[str] = None,
    scene_names: List[str] = None,
    max_samples: Optional[int] = 1024,
    resolution: Optional[str] = None,
    use_spectral_lensing: Optional[bool] = False,
):
    scenes = load_config()
    scenes = remove_unselected_configurations(
        scenes, only_hero_cam, integrators, scene_names
    )

    suite_count = 0
    test_count = 0
    for scene in scenes:
        suite = {}
        TEMPLATE["suites"].append(suite)
        suite["name"] = scene.name
        suite["tests"] = []
        settings_variations = itertools.product(
            scene.integrators,
            scene.intersectors,
            scene.cameras,
            scene.variant_set.variants if scene.variant_set else [None],
        )
        for (
            chosen_integrator,
            chosen_intersector,
            chosen_camera,
            chosen_variant,
        ) in settings_variations:
            variant_str = "-" + chosen_variant.lower() if chosen_variant else ""
            spectral_lensing_str = "-spectral" if use_spectral_lensing else ""
            test_name = f"{scene.name}-{os.path.basename(chosen_camera)}-{chosen_integrator.lower()}-{chosen_intersector.lower()}{variant_str}{spectral_lensing_str}"

            test = {
                "name": test_name,
                "variables": {
                    "scene_path": scene.scene_path,
                    "intersector": chosen_intersector,
                    "integrator": chosen_integrator,
                    "camera": chosen_camera,
                    "resolution": resolve_resolution(scene, resolution),
                    "maxSamples": str(max_samples),
                    "useSpectralLensing": "",
                },
            }
            if chosen_variant:
                test["variables"][
                    "selectedVariant"
                ] = f"--variantSelection {scene.variant_set.prim_path}:{scene.variant_set.variant_set}={chosen_variant}"
            if use_spectral_lensing:
                test["variables"]["useSpectralLensing"] = "--useSpectralLensing"

            suite["tests"].append(test)
            test_count += 1
        suite_count += 1
    with open("cato.json", "w") as f:
        json.dump(TEMPLATE, f, indent=4)

    print(f"Generated {suite_count} suites with {test_count} tests")


if __name__ == "__main__":
    app()
