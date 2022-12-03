#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
#include <scene/Scene.h>
#include "NaiveBvhNode.h"
namespace crayg {

class NaiveBvhBuilder {
 public:
    NaiveBvhBuilder(const Scene &scene);
    const Scene &scene;
    std::unique_ptr<NaiveBvh> build() const;
 private:
    void collectPrimitives(NaiveBvh &bvh) const;
    int collectPrimitiveCount() const;
};
}

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_BVHBUILDER_H_
