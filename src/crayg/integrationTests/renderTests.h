//
// Created by jan on 03/10/2019.
#include "KnipserAssertions.h"
#include "KnipserApp.h"
#include "renderUtils.h"

std::vector<KnipserTest> renderTests() {
    return {
        KnipserTest("singleSphere", [](TestContext &context) {
            context.setImageOutputName("singleSphere.png");
            renderScene(context.getReferenceFolder() + "/singleSphere.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        KnipserTest("threeSpheres", [](TestContext &context) {
            context.setImageOutputName("threeSpheres.png");
            renderScene(context.getReferenceFolder() + "/threeSpheres.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        }),
        KnipserTest("pointCloud", [](TestContext &context) {
            context.setImageOutputName("pointCloud.png");
            renderScene(context.getReferenceFolder() + "/pointCloud.json", context.getOutputFilename());

            ASSERT_IMAGES_ARE_EQUAL(context);
        })
    };
}