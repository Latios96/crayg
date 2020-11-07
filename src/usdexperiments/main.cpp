//
// Created by Jan on 05.11.2020.
//
#define NOMINMAX
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usd/primRange.h>
#include <iostream>

int main() {
    //pxr::SdfLayerRefPtr rootLayer = pxr::SdfLayer::FindOrOpen("N:\\Archiv\\2017\\The_Cement_Mixer\\Assets\\Prop\\Cement_Mixer\\Cement_Mixer_Maya\\Cement_Mixer_test.usd");
    auto stage = pxr::UsdStage::Open(
        R"(N:\Archiv\2017\The_Cement_Mixer\Assets\Prop\Cement_Mixer\Cement_Mixer_Maya\Cement_Mixer_test.usd)",
        pxr::UsdStage::LoadAll);
    for (auto prim : stage->Traverse()) {
        if (pxr::UsdGeomMesh(prim)) {
            std::cout << prim.GetName() << std::endl;
        }

    }
};
