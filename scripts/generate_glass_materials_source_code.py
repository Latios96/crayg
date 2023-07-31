import glob
from dataclasses import dataclass
from pathlib import Path
from typing import List
import xlrd


@dataclass
class Material:
    name: str
    ior: float
    abbe_no: float
    sellmeyer_coefficients: List[float]


def get_lens_materials_src_folder():
    return (
        Path(__file__).parent.parent
        / "src"
        / "crayg"
        / "src"
        / "scene"
        / "camera"
        / "realistic"
        / "materials"
    )


def find_catalog_xls(catalog_name):
    src_folder = get_lens_materials_src_folder()
    result = glob.glob(str(src_folder / f"{catalog_name}*.xls"))
    if not result:
        print(
            "no xls for catalog with name '' found. Please download the xls file from the manufacturer website"
        )
    return result[0]


def safe_name(name: str) -> str:
    return name.replace("-", "_").replace(" ", "_")


def process_schott() -> List[Material]:
    book = xlrd.open_workbook(find_catalog_xls("schott"))
    sh = book.sheet_by_index(0)

    materials = []

    for rx in range(sh.nrows):
        if rx < 4:
            continue
        name = safe_name(sh.cell_value(rowx=rx, colx=0)).upper()
        ior = sh.cell_value(rowx=rx, colx=1)
        abbe_no = sh.cell_value(rowx=rx, colx=4)
        coefficients = [sh.cell_value(rowx=rx, colx=x) for x in range(6, 12)]
        material = Material(name, ior, abbe_no, coefficients)
        materials.append(material)

    return materials


def process_ohara() -> List[Material]:
    book = xlrd.open_workbook(find_catalog_xls("OHARA"))
    sh = book.sheet_by_index(0)

    materials = []

    for rx in range(sh.nrows):
        if rx < 2:
            continue
        name = safe_name(sh.cell_value(rowx=rx, colx=1)).upper()
        ior = sh.cell_value(rowx=rx, colx=15)
        abbe_no = sh.cell_value(rowx=rx, colx=25)
        coefficients = [sh.cell_value(rowx=rx, colx=x) for x in range(60, 66)]
        material = Material(name, ior, abbe_no, coefficients)
        materials.append(material)

    return materials


def get_id_line(catalog_name: str, mat: Material) -> str:
    return f"{catalog_name.upper()}_{mat.name},\n"


def float_lit(f: float) -> str:
    return f"{f}f"


def get_constants_line(catalog_name: str, mat: Material) -> str:
    return f'case LensMaterialId::{catalog_name.upper()}_{mat.name}: return LensMaterial(LensMaterialId::{catalog_name.upper()}_{mat.name}, {float_lit(mat.ior)}, {float_lit(mat.abbe_no)}, {{{",".join(map(float_lit, mat.sellmeyer_coefficients))}}});\n'


def write_catalog(catalog_name: str, materials: List[Material]):
    with open(
        get_lens_materials_src_folder() / f"LensMaterialIds_{catalog_name.lower()}.h",
        "w",
    ) as f:
        f.writelines(map(lambda x: get_id_line(catalog_name, x), materials))

    with open(
        get_lens_materials_src_folder()
        / f"LensMaterialConstants_{catalog_name.lower()}.h",
        "w",
    ) as f:
        f.writelines(map(lambda x: get_constants_line(catalog_name, x), materials))


def main():
    materials_schott = process_schott()
    write_catalog("schott", materials_schott)

    materials_ohara = process_ohara()
    write_catalog("ohara", materials_ohara)


if __name__ == "__main__":
    main()
