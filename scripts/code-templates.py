import os
from dataclasses import dataclass
from pathlib import Path
from typing import List, Dict, Optional
import jinja2
import typer
from caseconverter import pascalcase


@dataclass
class Template:
    name: str
    path: str


ENUM_TEMPLATES = [
    Template(
        name="enum_header.jinja",
        path="{{directory}}/{{pascalcase(name)}}.h",
    )
]

CLASS_TEMPLATES = [
    Template(
        name="class_header.jinja",
        path="{{directory}}/{{pascalcase(name)}}.h",
    ),
    Template(
        name="class_cpp.jinja",
        path="{{directory}}/{{pascalcase(name)}}.cpp",
    ),
    Template(
        name="class_test.jinja",
        path="{{tests_directory}}/Test{{pascalcase(name)}}.cpp",
    ),
]

SHADING_NODE_TEMPLATES = [
    Template(
        name="shading_node_header.jinja",
        path="{{shading_nodes_directory}}/{{pascalcase(name)}}.h",
    ),
    Template(
        name="shading_node_cpp.jinja",
        path="{{shading_nodes_directory}}/{{pascalcase(name)}}.cpp",
    ),
    Template(
        name="shading_node_test.jinja",
        path="{{tests_directory}}/Test{{pascalcase(name)}}.cpp",
    ),
    Template(
        name="shading_node_writer_header.jinja",
        path="{{shading_node_writers_directory}}/Usd{{pascalcase(name)}}Writer.h",
    ),
    Template(
        name="shading_node_writer_cpp.jinja",
        path="{{shading_node_writers_directory}}/Usd{{pascalcase(name)}}Writer.cpp",
    ),
    Template(
        name="shading_node_writer_test.jinja",
        path="{{tests_directory}}/TestUsd{{pascalcase(name)}}Writer.cpp",
    ),
    Template(
        name="shading_node_reader_header.jinja",
        path="{{shading_node_readers_directory}}/Usd{{pascalcase(name)}}Reader.h",
    ),
    Template(
        name="shading_node_reader_cpp.jinja",
        path="{{shading_node_readers_directory}}/Usd{{pascalcase(name)}}Reader.cpp",
    ),
    Template(
        name="shading_node_reader_test.jinja",
        path="{{tests_directory}}/TestUsd{{pascalcase(name)}}Reader.cpp",
    ),
]


def _root_dir():
    return Path(__file__).parent.parent


def include_path(path: str) -> str:
    crayg_src_folder = str((_root_dir() / "src" / "crayg" / "src").absolute())
    include_path = (
        str(Path(path).absolute()).replace(crayg_src_folder, "")[1:].replace("\\", "/")
    )
    return include_path


def _get_tests_directory() -> str:
    return str(_root_dir() / "src" / "crayg" / "tests")


def _get_shading_nodes_directory() -> str:
    return str(
        _root_dir()
        / "src"
        / "crayg"
        / "src"
        / "scene"
        / "shadingnetworks"
        / "shadingnodes"
    )


def _get_shading_nodes_writers_directory() -> str:
    return str(
        _root_dir()
        / "src"
        / "crayg"
        / "src"
        / "sceneIO"
        / "write"
        / "usd"
        / "shadingnetworks"
        / "shadingnodes"
    )


def _get_shading_nodes_readers_directory() -> str:
    return str(
        _root_dir()
        / "src"
        / "crayg"
        / "src"
        / "sceneIO"
        / "read"
        / "usd"
        / "shadingnetworks"
        / "shadingnodes"
    )


def render_templates(
    templates: List[Template], variables: Dict[str, str]
) -> Dict[str, str]:
    rendered_files = {}
    env = jinja2.Environment(
        loader=jinja2.FileSystemLoader(Path(__file__).parent / "templates"),
        autoescape=jinja2.select_autoescape(),
    )

    default_vars = {
        "pascalcase": pascalcase,
        "include_path": include_path,
        "lower": lambda x: x.lower(),
        "tests_directory": _get_tests_directory(),
        "shading_nodes_directory": _get_shading_nodes_directory(),
        "shading_node_writers_directory": _get_shading_nodes_writers_directory(),
        "shading_node_readers_directory": _get_shading_nodes_readers_directory(),
    }
    default_vars.update(variables)
    for template in templates:
        file_path_jinja_template = jinja2.Template(template.path)
        file_path = file_path_jinja_template.render(**default_vars)
        jinja_template = env.get_template(template.name)
        rendered_template_text = jinja_template.render(**default_vars)
        rendered_files[file_path] = rendered_template_text
        print(f"generated file {file_path}")
    return rendered_files


def write_files(files: Dict[str, str]) -> None:
    for path, content in files.items():
        directory = os.path.dirname(path)
        if not os.path.exists(directory):
            os.makedirs(directory)
        with open(path, "w") as f:
            f.write(content)


app = typer.Typer()


@app.command(help="Generate an enum")
def create_enum(enum_name: str, directory: str):
    variables = {"name": enum_name, "directory": _root_dir() / directory}
    write_files(render_templates(ENUM_TEMPLATES, variables))


@app.command(help="Generate an class and coresponding test")
def create_class(class_name: str, directory: str):
    variables = {"name": class_name, "directory": _root_dir() / directory}
    write_files(render_templates(CLASS_TEMPLATES, variables))


@app.command(help="Generate a ShadingNode class, Usd{Reader,Writer} and tests")
def create_shading_node(node_name: str):
    variables = {"name": node_name, "directory": _get_shading_nodes_directory()}
    write_files(render_templates(SHADING_NODE_TEMPLATES, variables))


if __name__ == "__main__":
    app()
