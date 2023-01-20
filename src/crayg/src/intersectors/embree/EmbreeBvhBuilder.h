#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVHBUILDER_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVHBUILDER_H_

#include "EmbreeBvh.h"
namespace crayg {

class EmbreeBvhBuilder {
 public:
    EmbreeBvhBuilder(const Scene &scene);
    std::unique_ptr<EmbreeBvh> build() const;
 private:
    const Scene &scene;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVHBUILDER_H_