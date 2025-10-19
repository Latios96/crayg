#include "crayg/scene/io/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
#include "crayg/scene/io/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"
#include "crayg/scene/io/write/usd/shadingnetworks/shadingnodes/UsdFileTextureWriter.h"
#include "crayg/scene/primitives/Sphere.h"
#include "crayg/scene/shadingnetworks/shadingnodes/FileTexture.h"
#include "crayg/scene/shadingnetworks/shadingnodes/PrimVarReaders.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>

namespace crayg {

TEST_CASE("TestUsdFileTextureWriter::write") {
    auto stage = pxr::UsdStage::CreateInMemory();
    UsdPathFactory usdPathFactory;
    UsdShadingNodeWriteCache usdShadingNodeWriteCache(stage, usdPathFactory);

    SECTION("should write correctly") {
        auto uv = std::make_shared<PrimVarReaderVector2f>();
        FileTexture fileTexture;
        fileTexture.setFilePath("somefile.png");
        fileTexture.fallbackColor = Color(1, 2, 3);
        fileTexture.uvInput.connectTo(uv);
        UsdFileTextureWriter usdFileTextureWriter(fileTexture, usdShadingNodeWriteCache);

        auto shaderAndOutput = usdFileTextureWriter.writeAndGetShaderAndOutput(stage, usdPathFactory);

        REQUIRE(shaderAndOutput.shader.GetPath() == pxr::SdfPath("/FileTexture0"));
        REQUIRE(shaderAndOutput.output.GetFullName() == pxr::TfToken("outputs:out"));

        Color fallbackColor;
        UsdShadingNodeReadUtils::readShaderAttributeValue<Color, pxr::GfVec4f>(shaderAndOutput.shader, "fallbackColor",
                                                                               fallbackColor);
        REQUIRE(fallbackColor == Color(1, 2, 3));

        auto input = shaderAndOutput.shader.GetInput(pxr::TfToken("file"));
        pxr::SdfAssetPath path;
        input.Get(&path);
        REQUIRE(path == pxr::SdfAssetPath("somefile.png"));
    }
}

}