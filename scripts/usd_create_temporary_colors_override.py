import os
import subprocess
from typing import Tuple, Optional, Dict

import typer
from pxr import Usd, Sdf, UsdShade, Gf, UsdGeom


def parse_average_color_from_output(output) -> Optional[Gf.Vec3f]:
    lines = output.split("\n")
    for line in lines:
        if "Stats Avg:" in line:
            line = line.replace("Stats Avg:", "")
            line = line.replace("(of 255)", "")
            line = line.strip()
            color = tuple(map(lambda x: x / 255, map(float, line.split(" "))))
            return Gf.Vec3f(color[0], color[1], color[2])


def get_average_color_for_texture(texture_path: str) -> Optional[Gf.Vec3f]:
    print(f"Get average color for {texture_path}..")
    output = subprocess.getoutput(f"oiiotool --stats {texture_path}")
    return parse_average_color_from_output(output)


def get_surface_shader(prim):
    material = UsdShade.Material(prim)
    material.ComputeInterfaceInputConsumersMap()
    return material.ComputeSurfaceSource()[0]


def collect_average_material_colors(stage) -> Dict[str, Gf.Vec3f]:
    average_material_colors_by_material_path = {}

    for prim in stage.TraverseAll():
        if UsdShade.Material(prim):
            surface_shader = get_surface_shader(prim)
            if surface_shader:
                if not surface_shader.GetIdAttr().Get() == "UsdPreviewSurface":
                    continue
                diffuse_color = surface_shader.GetInput("diffuseColor")
                if diffuse_color.HasConnectedSource():
                    maybe_file_node = UsdShade.Shader(
                        diffuse_color.GetConnectedSource()[0].GetPrim()
                    )
                    if not maybe_file_node.GetIdAttr().Get() == "UsdUVTexture":
                        continue
                    resolved_path = maybe_file_node.GetInput("file").Get().resolvedPath
                    average_color = get_average_color_for_texture(resolved_path)
                    if not average_color:
                        continue
                    average_material_colors_by_material_path[
                        prim.GetPath()
                    ] = average_color
    return average_material_colors_by_material_path


def apply_material_average_color_overrides(
    stage, override_stage, average_material_colors_by_material_path
):
    for (
        material_path,
        average_color,
    ) in average_material_colors_by_material_path.items():
        surface_shader = get_surface_shader(stage.GetPrimAtPath(material_path))

        override_shader = override_stage.OverridePrim(surface_shader.GetPath())
        diffuse_color_override = override_shader.CreateAttribute(
            "inputs:diffuseColor", Sdf.ValueTypeNames.Color3f
        )
        diffuse_color_override.Set(average_color)


def apply_mesh_display_color_override(
    stage, override_stage, average_material_colors_by_material_path
):
    for prim in stage.TraverseAll():
        if UsdGeom.Mesh(prim):
            mesh = UsdGeom.Mesh(prim)
            binding_api = UsdShade.MaterialBindingAPI(mesh)
            material, _ = binding_api.ComputeBoundMaterial()
            color = average_material_colors_by_material_path.get(
                material.GetPrim().GetPath()
            )
            if color:
                override_prim = override_stage.OverridePrim(prim.GetPath())
                override_mesh = UsdGeom.Mesh(override_prim)
                display_color = override_mesh.CreateDisplayColorAttr()
                display_color.Set([color])


def main(usd_file: str):
    temporary_colors_layer_path = os.path.join(
        os.path.dirname(usd_file), "temporary_colors.usda"
    )
    print(f"Opening stage {usd_file}..")
    stage = Usd.Stage.Open(usd_file)
    override_stage = Usd.Stage.CreateNew(temporary_colors_layer_path)

    average_material_colors_by_material_path = collect_average_material_colors(stage)
    apply_material_average_color_overrides(
        stage, override_stage, average_material_colors_by_material_path
    )
    apply_mesh_display_color_override(
        stage, override_stage, average_material_colors_by_material_path
    )

    stage.GetRootLayer().subLayerPaths.insert(0, "./temporary_colors.usda")
    print(f"Saving {temporary_colors_layer_path}..")
    override_stage.Save()
    print(f"Saving {usd_file}..")
    stage.Save()


if __name__ == "__main__":
    typer.run(main)
