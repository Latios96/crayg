#include "UsdPrimVarReaderReaders.h"

namespace crayg {

UsdPrimVarReaderVector2fReader::UsdPrimVarReaderVector2fReader(const pxr::UsdShadeShader &usdPrim,
                                                               UsdShadingNodeReadCache &usdShadingNodeReadCache)
    : BaseUsdShadingNodeReader(usdPrim, usdShadingNodeReadCache) {
}

std::shared_ptr<PrimVarReaderVector2f> UsdPrimVarReaderVector2fReader::read() {
    auto primVarReader = BaseUsdShadingNodeReader::read();

    const auto id = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdPrim.GetIdAttr());
    if (id == pxr::TfToken("UsdPrimvarReader_float2")) {
        readPrimVarReaderTypeFromUsd(primVarReader);
    } else if (id == pxr::TfToken("crayg:PrimVarReaderVector2f")) {
        readPrimVarReaderTypeFromCrayg(primVarReader);
    }

    return primVarReader;
}

std::string UsdPrimVarReaderVector2fReader::getTranslatedType() {
    return "UsdPrimVarReaderVector2fReader";
}

bool primVarIsUVs(const std::string &varname) {
    return varname == "st" || varname == "UVMap";
}

void UsdPrimVarReaderVector2fReader::readPrimVarReaderTypeFromUsd(
    std::shared_ptr<PrimVarReaderVector2f> &primVarReader) {
    pxr::UsdShadeConnectableAPI connectedOutput;
    pxr::TfToken connectedOutputName;
    pxr::UsdShadeAttributeType type;
    usdPrim.ConnectableAPI().GetConnectedSource(usdPrim.GetInput(pxr::TfToken("varname")), &connectedOutput,
                                                &connectedOutputName, &type);
    const auto varnameInput = connectedOutput.GetInput(connectedOutputName);
    if (!varnameInput) {
        primVarReader->primVarReaderType = PrimVarReaderType::UNKNOWN;
        return;
    }

    const auto varname = UsdUtils::getStaticAttributeValueAs<std::string>(varnameInput);
    if (primVarIsUVs(varname)) {
        primVarReader->primVarReaderType = PrimVarReaderType::UV;
        return;
    }
    primVarReader->primVarReaderType = PrimVarReaderType::UNKNOWN;
    Logger::warning("PrimVarReader {} has unknown varname {} specified, falling back to PrimVarReaderType::UNKNOWN",
                    usdPrim.GetPath(), varname);
}

void UsdPrimVarReaderVector2fReader::readPrimVarReaderTypeFromCrayg(
    std::shared_ptr<PrimVarReaderVector2f> &primVarReader) {
    primVarReader->primVarReaderType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "primVarReaderType", PrimVarReaderType::UNKNOWN);
}

} // crayg