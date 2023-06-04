#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_

#include "CraygUsdBase.h"
#include "UsdTypeUtil.h"
#include "utils/EnumUtils.h"
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
        throw std::runtime_error(fmt::format(
            "Attribute '{}': There was no attribute value to read or attribute was not of the type requested",
            attribute.GetName()));
    };

    template <typename T> static T getStaticAttributeValueAs(const pxr::UsdAttribute attribute) {
        return getAttributeValueAs<T>(attribute, pxr::UsdTimeCode::Default());
    };

    template <typename T>
    static T getAttributeValueAs(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue,
                                 const pxr::UsdTimeCode timeCodeToRead) {
        auto usdAttr = usdPrim.GetAttribute(pxr::TfToken(attributeName));
        if (!usdAttr) {
            return defaultValue;
        }
        return getAttributeValueAs<T>(usdAttr, timeCodeToRead);
    };

    template <typename T>
    static T getStaticAttributeValueAs(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue) {
        return getAttributeValueAs<T>(usdPrim, attributeName, defaultValue, pxr::UsdTimeCode::Default());
    };

    template <typename T>
    static T getAttributeValueAsEnum(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue) {
        auto usdAttr = usdPrim.GetAttribute(pxr::TfToken(attributeName));
        if (!usdAttr) {
            return defaultValue;
        }

        const bool enumValueAuthoredAsToken = usdAttr.GetTypeName() == pxr::SdfValueTypeNames->Token;
        const bool enumValueAuthoredAsString = usdAttr.GetTypeName() == pxr::SdfValueTypeNames->String;
        const bool enumValueAuthoredAsInt = usdAttr.GetTypeName() == pxr::SdfValueTypeNames->Int;

        if (!enumValueAuthoredAsToken && !enumValueAuthoredAsInt && !enumValueAuthoredAsString) {
            throw std::runtime_error(fmt::format("USD attribute {} has type {}, which is not supported for enum",
                                                 attributeName, usdAttr.GetTypeName()));
        }

        if (enumValueAuthoredAsToken) {
            return getEnumValueFromTokenAttr(usdAttr, attributeName, defaultValue);
        } else if (enumValueAuthoredAsString) {
            return getEnumValueFromStringAttr(usdAttr, attributeName, defaultValue);
        }
        return getEnumValueFromIntAttr(usdAttr, attributeName, defaultValue);
    }

    template <typename T>
    static void createAndSetAttribute(pxr::UsdPrim usdPrim, const std::string &attributeName, T defaultValue) {
        usdPrim.CreateAttribute(pxr::TfToken(attributeName), UsdTypeUtil<T>::sdfValueTypeName)
            .Set(UsdTypeUtil<T>::convert(defaultValue));
    }

    static void createAndSetAttribute(pxr::UsdPrim usdPrim, const std::string &attributeName,
                                      pxr::SdfAssetPath defaultAssetPath) {
        usdPrim.CreateAttribute(pxr::TfToken(attributeName), pxr::SdfValueTypeNames->Asset).Set(defaultAssetPath);
    }

  private:
    template <typename T>
    static T getEnumValueFromTokenAttr(const pxr::UsdAttribute usdAttr, const std::string &attributeName,
                                       T defaultValue) {
        auto tokenValue = UsdUtils::getStaticAttributeValueAs<pxr::TfToken>(usdAttr).GetString();
        return EnumUtils::parseOrDefault(tokenValue, defaultValue);
    }

    template <typename T>
    static T getEnumValueFromIntAttr(const pxr::UsdAttribute usdAttr, const std::string &attributeName,
                                     T defaultValue) {
        auto tokenValue = UsdUtils::getStaticAttributeValueAs<int>(usdAttr);
        return EnumUtils::parseOrDefault(tokenValue, defaultValue);
    }

    template <typename T>
    static T getEnumValueFromStringAttr(const pxr::UsdAttribute usdAttr, const std::string &attributeName,
                                        T defaultValue) {
        auto tokenValue = UsdUtils::getStaticAttributeValueAs<std::string>(usdAttr);
        return EnumUtils::parseOrDefault(tokenValue, defaultValue);
    }
};

}

#endif // CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
