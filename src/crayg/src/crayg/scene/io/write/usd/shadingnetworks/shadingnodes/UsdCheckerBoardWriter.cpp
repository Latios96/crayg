#include "UsdCheckerBoardWriter.h"
#include "crayg/scene/io/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h"

namespace crayg {
UsdCheckerBoardWriter::UsdCheckerBoardWriter(CheckerBoard &craygObject,
                                             UsdShadingNodeWriteCache &usdShadingNodeWriteCache)
    : BaseUsdShadingNodeWriter(craygObject, usdShadingNodeWriteCache) {
}

pxr::UsdShadeShader UsdCheckerBoardWriter::write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) {
    auto usdCheckerBoard = BaseUsdShadingNodeWriter::write(stage, usdPathFactory);

    usdCheckerBoard.CreateIdAttr(pxr::VtValue(pxr::TfToken("crayg:CheckerBoard")));
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdCheckerBoard, "colorA", craygObject.colorA);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdCheckerBoard, "colorB", craygObject.colorB);
    usdShadingNodeWriteCache.createInputAndWriteCachedGraph(usdCheckerBoard, "uvInput", craygObject.uvInput);
    usdCheckerBoard.CreateInput(pxr::TfToken("repetitions"), pxr::SdfValueTypeNames->Int).Set(craygObject.repetitions);
    usdCheckerBoard.CreateOutput(pxr::TfToken("out"), pxr::SdfValueTypeNames->Color3f);

    return usdCheckerBoard;
}

pxr::UsdShadeOutput UsdCheckerBoardWriter::getOutput(pxr::UsdShadeShader &usdShadeShader) {
    return usdShadeShader.GetOutput(pxr::TfToken("out"));
}

std::string UsdCheckerBoardWriter::getTranslatedType() {
    return "CheckerBoard";
}
}