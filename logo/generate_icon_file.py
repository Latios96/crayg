import os
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import List


@dataclass
class IconSet:
    name: str
    color: str
    background_color: str
    resolutions: List[int]

    def identifier(self):
        return f"{self.name}_{self.color}_{self.background_color}"

    def get_name(self, resolution):
        return f"{self.identifier()}_{resolution}x{resolution}.png"

    def get_names(self):
        for resolution in sorted(self.resolutions):
            yield self.get_name(resolution)


def load_icon_sets():
    folder = Path(__file__).parent
    files = folder.glob("*.png")
    icon_set_sizes = {}

    for f in files:
        match = re.search('(?P<name>\w+)_(?P<color>\w+)_(?P<background_color>\w+)_(?P<size>\d+)x\d+', str(f.name))
        if not match:
            continue
        name = match.group("name")
        color = match.group("color")
        background_color = match.group("background_color")
        identifier = (name, color, background_color)
        icon_set = icon_set_sizes.get(identifier)
        if not icon_set:
            icon_set = IconSet(name=name, color=color,
                               background_color=background_color, resolutions=[])
            icon_set_sizes[identifier] = icon_set
        icon_set.resolutions.append(int(match.group("size")))
    return list(icon_set_sizes.values())


def generate_ico_file(icon_sets: List[IconSet]):
    for icon_set in icon_sets:
        command = ["magick", "convert", *icon_set.get_names(), f"generated/{icon_set.identifier()}.ico"]
        print(f"Converting {icon_set.identifier()} to .ico..")
        subprocess.call(command)


def generate_icns_file(icon_sets: List[IconSet]):
    with tempfile.TemporaryDirectory() as tmpdir:
        for icon_set in icon_sets:
            if "LogoFull" in icon_set.name:
                continue
            print(f"Converting {icon_set.identifier()} to .icns..")
            for resolution in icon_set.resolutions:
                icon_set_folder_path = Path(tmpdir).parent / "iconTest" / f"{icon_set.identifier().replace('_', '')}.iconset"
                target = icon_set_folder_path / f"icon_{resolution}x{resolution}.png"
                target_scaled = icon_set_folder_path / f"icon_{resolution}x{resolution}@2x.png"
                if not target.parent.exists():
                    os.makedirs(target.parent)
                shutil.copy(icon_set.get_name(resolution), target)
                if resolution not in [16, 2048]:
                    shutil.copy(icon_set.get_name(int(resolution * 2)), target_scaled)
            command = ["iconutil", "-c", "icns", str(icon_set_folder_path)]
            subprocess.call(command)
            shutil.copy(str(icon_set_folder_path).replace(".iconset", ".icns"),
                        Path(__file__).parent / "generated"/(icon_set.identifier() + ".icns"))


def ensure_generated_folder():
    generated_folder = Path(__file__).parent / "generated"
    if not generated_folder.exists():
        generated_folder.mkdir()


def main():
    icon_sets = load_icon_sets()
    ensure_generated_folder()
    generate_ico_file(icon_sets)
    if sys.platform == "darwin":
        generate_icns_file(icon_sets)


if __name__ == '__main__':
    main()
