//
// Created by Jan on 13.05.2022.
//

#ifndef CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
#define CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_

#include <pxr/usd/usd/attribute.h>

namespace crayg {

class UsdUtils {

 public:
    template<typename T>
    static T getAttributeValueAs(const pxr::UsdAttribute attribute) {
        T value;
        attribute.Get(&value);
        return value;
    };

};

}

#endif //CRAYG_SRC_CRAYGUSD_SRC_USDUTILS_H_
