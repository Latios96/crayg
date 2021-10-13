//
// Created by Jan on 13.10.2021.
//

#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#include <scene/Scene.h>
#include "BvhNode.h"
namespace crayg {
class BvhBuilder {
 public:
    BvhBuilder(const Scene &scene);
    const Scene &scene;
    [[nodiscard]] BvhNode *build() const;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
