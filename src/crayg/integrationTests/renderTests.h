//
// Created by jan on 03/10/2019.
#include "KnipserAssertions.h"
#include "KnipserApp.h"
#include "renderUtils.h"

namespace crayg {

std::vector<knipser::KnipserTest> renderTests() {
    return {
        knipser::KnipserTest("singleSphere", [](knipser::TestContext &context) {
            context.setImageOutputName("singleSphere.png");
            renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        knipser::KnipserTest("threeSpheres", [](knipser::TestContext &context) {
            context.setImageOutputName("threeSpheres.png");
            renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        knipser::KnipserTest("pointCloud", [](knipser::TestContext &context) {
            context.setImageOutputName("pointCloud.png");
            renderScene(context.getReferenceFolder() + "/pointCloud.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        knipser::KnipserTest("teapot", [](knipser::TestContext &context) {
            context.setImageOutputName("teapot.png");
            renderScene(context.getReferenceFolder() + "/teapot.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        knipser::KnipserTest("singleSphereWithMats", [](knipser::TestContext &context) {
            context.setImageOutputName("singleSphereWithMats.png");
            renderScene(context.getReferenceFolder() + "/singleSphereWithMats.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        knipser::KnipserTest("singleSphereWithDiskLight", [](knipser::TestContext &context) {
            context.setImageOutputName("singleSphereWithDiskLight.png");
            renderScene(context.getReferenceFolder() + "/singleSphereWithDiskLight.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
    };
}

}