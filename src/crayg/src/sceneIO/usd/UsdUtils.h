#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_

#include "CraygUsdBase.h"
#include "UsdTypeUtil.h"
#include <magic_enum.hpp>
#include <pxr/usd/usd/attribute.h>
#include <type_traits>

namespace crayg {

class UsdUtils {

  public:
    template <typename T>
    static T getAttributeValueAs(const pxr::UsdAttribute attribute, const pxr::UsdTimeCode timeCodeToRead) {
        T value;
        if (attribute.Get(&value, timeCodeToRead)) {
            return value;
        }
        throw std::runtime_error("There was no attribute value to read or attribute was not of the type requested");
    };

    template <typename T> static T getStaticAttributeValueAs(const pxr::UsdAttribute attribute) {
        return getAttributeValueAs<T>(attribute, pxr::UsdTimeCode::Default());
    };

    template <typename T>
    static T getAttributeValueAsEnum(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue) {
        auto usdAttr = usdPrim.GetAttribute(pxr::TfToken(attributeName));
        if (!usdAttr) {
            return defaultValue;
        }
        auto tokenValue = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdAttr).GetString();
        for (auto &c : tokenValue) {
            c = toupper(c);
        }
        auto maybeValue = magic_enum::enum_cast<T>(tokenValue);
        if (!maybeValue.has_value()) {
            throw std::runtime_error(fmt::format(R"(Unsupported value for '{}': "{}")", attributeName, tokenValue));
        }
        return maybeValue.value();
    }

    template <typename T>
    static void createAndSetAttribute(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue) {
        usdPrim.CreateAttribute(pxr::TfToken(attributeName), UsdTypeUtil<T>::sdfValueTypeName)
            .Set(UsdTypeUtil<T>::convert(defaultValue));
    }
};

}

#endif // CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
