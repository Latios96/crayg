import argparse

from pxr import Usd, Gf, UsdGeom

ZERO_VEC = Gf.Vec3f(0, 0, 0)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("stage_path")
    args = parser.parse_args()

    print(f"Opening stage {args.stage_path}..")
    stage = Usd.Stage.Open(args.stage_path)

    print(f"Begin to traverse stage..")
    for prim in stage.TraverseAll():
        if UsdGeom.Mesh(prim):
            mesh = UsdGeom.Mesh(prim)
            normals = mesh.GetNormalsAttr().Get()
            needs_fix = False
            for normal in normals:
                if normal == ZERO_VEC:
                    needs_fix = True
                    break
            if needs_fix:
                mesh.GetNormalsAttr().Set([])
                print(f"fixed normals for {prim.GetPath()}")

    print(f"Saving stage")
    stage.Save()


if __name__ == "__main__":
    main()
