#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_

#include "CraygUsdBase.h"
#include <pxr/usd/usd/attribute.h>

namespace crayg {

class UsdUtils {

 public:
    template<typename T>
    static T getAttributeValueAs(const pxr::UsdAttribute attribute, const pxr::UsdTimeCode timeCodeToRead) {
        T value;
        if (attribute.Get(&value, timeCodeToRead)) {
            return value;
        }
        throw std::runtime_error("There was no attribute value to read or attribute was not of the type requested");
    };

    template<typename T>
    static T getStaticAttributeValueAs(const pxr::UsdAttribute attribute) {
        return getAttributeValueAs<T>(attribute, pxr::UsdTimeCode::Default());
    };

};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
