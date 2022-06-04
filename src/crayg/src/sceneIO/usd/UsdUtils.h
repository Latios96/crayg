//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_

#include "CraygUsdBase.h"
#include <pxr/usd/usd/attribute.h>

namespace crayg {

class UsdUtils {

 public:
    template<typename T>
    static T getAttributeValueAs(const pxr::UsdAttribute attribute) {
        T value;
        if (attribute.Get(&value)) {
            return value;
        }
        throw std::runtime_error("There was no attribute value to read or attribute was not of the type requested");
    };

};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
