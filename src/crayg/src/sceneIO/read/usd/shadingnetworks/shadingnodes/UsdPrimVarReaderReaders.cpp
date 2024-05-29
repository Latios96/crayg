#include "UsdPrimVarReaderReaders.h"
#include <pxr/usd/sdf/types.h>

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

    std::string varname = getVarname(varnameInput);
    if (primVarIsUVs(varname)) {
        primVarReader->primVarReaderType = PrimVarReaderType::UV;
        return;
    }
    primVarReader->primVarReaderType = PrimVarReaderType::UNKNOWN;
    Logger::warning("PrimVarReader {} has unknown varname {} specified, falling back to PrimVarReaderType::UNKNOWN",
                    usdPrim.GetPath(), varname);
}

std::string UsdPrimVarReaderVector2fReader::getVarname(const pxr::UsdShadeInput &varnameInput) const {
    if (varnameInput.GetTypeName() == pxr::SdfValueTypeNames->String) {
        return UsdUtils::getStaticAttributeValueAs<std::string>(varnameInput);
    } else if (varnameInput.GetTypeName() == pxr::SdfValueTypeNames->Token) {
        const auto varnameToken = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(varnameInput);
        return varnameToken.GetString();
    }
    CRAYG_LOG_AND_THROW_MESSAGE(fmt::format("varname attribute has unknown type {} on {}",
                                            varnameInput.GetTypeName().GetAsToken(), varnameInput.GetPrim().GetPath()))
}

void UsdPrimVarReaderVector2fReader::readPrimVarReaderTypeFromCrayg(
    std::shared_ptr<PrimVarReaderVector2f> &primVarReader) {
    primVarReader->primVarReaderType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "primVarReaderType", PrimVarReaderType::UNKNOWN);
}

} // crayg