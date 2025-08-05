#include "UsdPrimVarReaderReaders.h"
#include "sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h"
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

    const auto varname = getVarname();
    if (!varname) {
        primVarReader->primVarReaderType = PrimVarReaderType::UNKNOWN;
        Logger::warning("PrimVarReader {} has no varname {} specified, falling back to PrimVarReaderType::UNKNOWN",
                        usdPrim.GetPath(), *varname);
        return;
    }

    if (primVarIsUVs(*varname)) {
        primVarReader->primVarReaderType = PrimVarReaderType::UV;
        return;
    }
    primVarReader->primVarReaderType = PrimVarReaderType::UNKNOWN;
    Logger::warning("PrimVarReader {} has unknown varname {} specified, falling back to PrimVarReaderType::UNKNOWN",
                    usdPrim.GetPath(), *varname);
}

void UsdPrimVarReaderVector2fReader::readPrimVarReaderTypeFromCrayg(
    std::shared_ptr<PrimVarReaderVector2f> &primVarReader) {
    primVarReader->primVarReaderType =
        UsdUtils::getAttributeValueAsEnum(usdPrim.GetPrim(), "primVarReaderType", PrimVarReaderType::UNKNOWN);
}

std::optional<std::string> UsdPrimVarReaderVector2fReader::getVarname() {
    const auto varnameFromCurrentNode = getVarnameFromCurrentNode();
    if (varnameFromCurrentNode) {
        return varnameFromCurrentNode;
    }

    const auto varnameFromConnectedNode = getVarnameFromConnectedNode();
    if (varnameFromConnectedNode) {
        return varnameFromConnectedNode;
    }

    return std::nullopt;
}

std::optional<std::string> UsdPrimVarReaderVector2fReader::getVarnameFromCurrentNode() {
    const auto input = usdPrim.GetInput(pxr::TfToken("varname"));

    if (input.HasConnectedSource()) {
        return std::nullopt;
    }

    return readVarname(input);
}

std::optional<std::string> UsdPrimVarReaderVector2fReader::getVarnameFromConnectedNode() {
    pxr::UsdShadeConnectableAPI connectedOutput;
    pxr::TfToken connectedOutputName;
    pxr::UsdShadeAttributeType type;
    usdPrim.ConnectableAPI().GetConnectedSource(usdPrim.GetInput(pxr::TfToken("varname")), &connectedOutput,
                                                &connectedOutputName, &type);
    const auto varnameInput = connectedOutput.GetInput(connectedOutputName);
    if (!varnameInput) {
        return std::nullopt;
    }

    return readVarname(varnameInput);
}

std::string UsdPrimVarReaderVector2fReader::readVarname(const pxr::UsdShadeInput &varnameInput) const {
    if (varnameInput.GetTypeName() == pxr::SdfValueTypeNames->String) {
        return UsdUtils::getStaticAttributeValueAs<std::string>(varnameInput);
    } else if (varnameInput.GetTypeName() == pxr::SdfValueTypeNames->Token) {
        const auto varnameToken = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(varnameInput);
        return varnameToken.GetString();
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("varname attribute has unknown type {} on {}",
                                      varnameInput.GetTypeName().GetAsToken(), varnameInput.GetPrim().GetPath())
}

}