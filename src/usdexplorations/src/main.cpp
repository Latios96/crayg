#include <iostream>
#define NOMINMAX
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/imaging/hd/meshUtil.h>
#include <pxr/imaging/hd/meshTopology.h>
#include <pxr/base/vt/array.h>
#include <scene/TriangleMesh.h>
#include <utils/StopWatch.h>
#include "scene/Scene.h"
#include "image/Image.h"
#include "image/ImageOutputDriver.h"
#include "Renderer.h"
#include "utils/ImagePathResolver.h"
#include "scene/DiffuseMaterial.h"
#include <image/ImageWriters.h>

int main(int argc, char *argv[]) {
    crayg::StopWatch stopWatchOpeningState = crayg::StopWatch::createStopWatch("Opening stage");
    auto stage = pxr::UsdStage::Open("M:\\modelLibrary\\_input_to_convert\\Kitchen_set\\Kitchen_set\\Kitchen_set.usd");
    //auto stage = pxr::UsdStage::Open("C:\\workspace\\crayg\\example_scenes\\polyPlane.usda");
    stopWatchOpeningState.end();

    crayg::StopWatch stopWatchConvertMeshes = crayg::StopWatch::createStopWatch("Converting meshes");
    crayg::RenderSettings renderSettings(crayg::Resolution(1280, 720), 1);
    crayg::Scene scene;
    scene.renderSettings = renderSettings;
    scene.camera = std::make_shared<crayg::Camera>(crayg::Vector3f(362, -27, 107),
                                                   crayg::Vector3f(0, 1, 0),
                                                   crayg::Vector3f(-1, 0, 0),
                                                   35.0f,
                                                   36.0f);

    auto defaultMaterial = std::make_shared<crayg::DiffuseMaterial>("defaultMaterial", crayg::Color::createWhite());

    for (pxr::UsdPrim prim: stage->TraverseAll()) {
        if (prim.IsA<pxr::UsdGeomMesh>()) {
            pxr::UsdGeomMesh mesh(prim);
            pxr::TfToken scheme;
            mesh.GetSubdivisionSchemeAttr().Get(&scheme);
            pxr::TfToken orientation;
            mesh.GetOrientationAttr().Get(&orientation);
            pxr::VtIntArray faceVertexCounts, faceVertexIndices, holeIndices;
            mesh.GetFaceVertexCountsAttr().Get(&faceVertexCounts);
            mesh.GetFaceVertexIndicesAttr().Get(&faceVertexIndices);
            mesh.GetHoleIndicesAttr().Get(&holeIndices);
            pxr::HdMeshTopology topology(scheme, orientation, faceVertexCounts, faceVertexIndices, holeIndices);
            pxr::HdMeshUtil meshUtil(&topology, mesh.GetPath());
            pxr::VtVec3iArray triangleIndices;
            pxr::VtIntArray primitiveParams;
            meshUtil.ComputeTriangleIndices(&triangleIndices, &primitiveParams);

            auto triangleMesh = std::make_shared<crayg::TriangleMesh>();
            pxr::VtVec3fArray points;
            mesh.GetPointsAttr().Get(&points);
            triangleMesh->points.reserve(points.size());
            for (const auto &point: points) {
                triangleMesh->points.emplace_back(point[0], point[1], point[2]);
            }
            triangleMesh->faceIndexes.reserve(triangleIndices.size());
            for (const auto &faceIndex: triangleIndices) {
                triangleMesh->faceIndexes.push_back(faceIndex[0]);
                triangleMesh->faceIndexes.push_back(faceIndex[1]);
                triangleMesh->faceIndexes.push_back(faceIndex[2]);
            }
            triangleMesh->init();
            /*pxr::GfMatrix4d matrix;
            bool resetsXformStack = false;
            mesh.GetLocalTransformation(&matrix, &resetsXformStack);
            std::cout << matrix << std::endl;*/
            triangleMesh->setMaterial(defaultMaterial);
            scene.addObject(triangleMesh);
        }
    }
    stopWatchConvertMeshes.end();

    auto light = std::make_shared<crayg::Light>(crayg::Transform::withPosition({0, 0, 130}), 1);
    scene.addLight(light);

    crayg::Image myImage(scene.renderSettings.resolution);

    crayg::ImageOutputDriver imageOutputDriver(myImage);

    crayg::Renderer renderer(scene, imageOutputDriver);
    renderer.renderScene();

    crayg::ImagePathResolver imagePathResolver;
    std::string imageOutputPath = imagePathResolver.resolve("usdexplore.png");
    crayg::Logger::info("writing image to {}..", imageOutputPath);
    crayg::ImageWriters::writeImage(myImage, imageOutputPath);
    crayg::Logger::info("writing image done.");

    return 0;
}

