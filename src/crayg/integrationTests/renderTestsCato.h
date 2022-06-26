//
// Created by jan on 03/10/2019.
#include "KnipserAssertions.h"
#include "KnipserApp.h"
#include "renderUtils.h"

namespace crayg {

std::string getPath(std::string folder, std::string suiteName, std::string testName) {
    return (boost::filesystem::path(folder).parent_path().parent_path() / suiteName / testName / testName).string();
}

void catoTest(knipser::TestContext &context, std::string suiteName, std::string testName) {
    context.setImageOutputName(fmt::format("{}_{}.png", suiteName, testName));

    renderScene(getPath(context.getReferenceFolder(), suiteName, testName) + ".usda",
                context.getOutputFilename(), Resolution(960, 540));

    knipser::BasicAssertion referenceImageExists(__FILE__, __LINE__);
    std::string referenceImagePath = getPath(context.getReferenceFolder(), suiteName, testName) + ".png";
    referenceImageExists.doAssert(boost::filesystem::exists(referenceImagePath),
                                  fmt::format("Reference image {} does not exist!", referenceImagePath));
    knipser::BasicAssertion outputFileNameExists(__FILE__, __LINE__);
    outputFileNameExists.doAssert(boost::filesystem::exists(context.getOutputFilename()),
                                  fmt::format("Output image {} does not exist!", context.getOutputFilename()));
    knipser::OpenImageIoImageComparator imageComparator(referenceImagePath, context.getOutputFilename());
    knipser::ImageComparatorResult result = imageComparator.compareImages();
    knipser::BasicAssertion imageAreEqual(__FILE__, __LINE__);
    imageAreEqual.doAssert(!result.isError(),
                           fmt::format("Images {} and {} are not equal!!!",
                                       referenceImagePath,
                                       context.getOutputFilename()));
}
std::vector<knipser::KnipserTest> renderTestsCato() {
    return {
        knipser::KnipserTest("Lights_SinglePointLight", [](knipser::TestContext &context) {
            catoTest(context, "Lights", "SinglePointLight");
        }),
        knipser::KnipserTest("Lights_SingleRectLight", [](knipser::TestContext &context) {
            catoTest(context, "Lights", "SingleRectLight");
        }),
        /*TODO fix this test
         * knipser::KnipserTest("Lights_SingleDiskLight", [](knipser::TestContext &context) {
            catoTest(context, "Lights", "SingleDiskLight");
        }),*/
        knipser::KnipserTest("Lights_MultiplePointLights", [](knipser::TestContext &context) {
            catoTest(context, "Lights", "MultiplePointLights");
        }),
        knipser::KnipserTest("Lights_MultipleColoredPointLights", [](knipser::TestContext &context) {
            catoTest(context, "Lights", "MultipleColoredPointLights");
        }),
    };
}

}