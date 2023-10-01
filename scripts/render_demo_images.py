import subprocess
import sys
import uuid
from dataclasses import dataclass
from pathlib import Path
from typing import Tuple, Optional, List
import requests
import typer as typer


@dataclass
class DemoImage:
    name: str
    scene_path: Path
    max_samples: int
    resolution: Tuple[int, int]
    camera: Optional[str] = None

    def output_path(self, directory: Path, extension=".png"):
        return directory / (self.name + extension)


def get_repository_root() -> Path:
    return Path(__file__).parent.parent


def resolve_path(path: str) -> Path:
    return get_repository_root() / path


def get_executable():
    return resolve_path("cmake-build-relwithdebinfo/bin/crayg-standalone.exe")


def generate_render_command(demo_image: DemoImage, output_dir: Path) -> str:
    command = f"{get_executable()} -s {demo_image.scene_path} -o {demo_image.output_path(output_dir)} --maxSamples {demo_image.max_samples} --resolution {demo_image.resolution[0]}x{demo_image.resolution[1]}"
    if demo_image.camera:
        command += f" --camera {demo_image.camera}"
    return command


def render_demo_images_locally(demo_images: List[DemoImage]) -> None:
    for demo_image in demo_images:
        command = generate_render_command(demo_image, resolve_path("images"))
        subprocess.check_call(command)


def render_demo_images_with_deadline(demo_images: List[DemoImage]) -> None:
    jobs = []

    batch_id = str(uuid.uuid4()).split("-")[0]

    for demo_image in demo_images:
        output_path = demo_image.output_path(resolve_path("images"))
        job_info = {
            "Plugin": "Crayg",
            "Name": demo_image.name,
            "BatchName": f"Crayg Demo Images {batch_id}",
            "OutputDirectory0": str(output_path.parent),
            "OutputFilename0": str(output_path.name),
            "FailureDetectionJobErrors": 1,
            "FailureDetectionTaskErrors": 1,
            "OverrideJobFailureDetection": True,
            "OverrideTaskFailureDetection": True,
        }

        plugin_info = {
            "CraygExecutable": str(get_executable()),
            "Scene": str(demo_image.scene_path),
            "Resolution": f"{demo_image.resolution[0]}x{demo_image.resolution[1]}",
            "MaxSamples": demo_image.max_samples,
        }
        if demo_image.camera:
            plugin_info["Camera"] = demo_image.camera

        jobs.append({"JobInfo": job_info, "PluginInfo": plugin_info, "AuxFiles": []})

    json_data = {"Jobs": jobs}

    requests.post("http://127.0.0.1:8081/api/jobs", json=json_data)


def get_demo_images(max_samples=32):
    demo_images = []
    demo_images.append(
        DemoImage(
            name="CornellBox_Original_GI",
            scene_path=resolve_path(
                "src\crayg\integrationTests\CornellBox\CornellBox_Original_GI\CornellBox_Original_GI.usda"
            ),
            max_samples=max_samples,
            resolution=(800, 800),
        )
    )
    demo_images.append(
        DemoImage(
            name=f"StormTrooper",
            scene_path=Path("M:\Test_Scene_Collection\StormTrooper\StormTrooper.usda"),
            max_samples=max_samples,
            resolution=(1920, 1080),
            camera=f"/root/Camera/render_cam",
        )
    )
    for i in range(1, 7):
        camera_number = f"{i}".zfill(3)
        demo_images.append(
            DemoImage(
                name=f"Intel_Sponza_PhysCamera{camera_number}",
                scene_path=Path("M:\Test_Scene_Collection\Intel_Sponza\Default.usda"),
                max_samples=max_samples,
                resolution=(1280, 720),
                camera=f"/PhysCamera{camera_number}",
            )
        )
    for camera_number in range(1, 8):
        demo_images.append(
            DemoImage(
                name=f"OpenChessSet_render_cam_{camera_number}",
                scene_path=Path(
                    "M:\Test_Scene_Collection\OpenChessSet\OpenChessSetCrayg.usda"
                ),
                max_samples=max_samples,
                resolution=(1920, 1080),
                camera=f"/cams/render_cam_{camera_number}/render_cam_{camera_number}Shape",
            )
        )
    return demo_images


app = typer.Typer()


@app.command(help="Render demo images locally")
def render_local(max_samples: Optional[int] = 32):
    demo_images = get_demo_images(max_samples)
    render_demo_images_locally(demo_images)


@app.command(help="Render demo images using AWS Deadline")
def submit(max_samples: Optional[int] = 32):
    demo_images = get_demo_images(max_samples)
    render_demo_images_with_deadline(demo_images)


if __name__ == "__main__":
    app()
