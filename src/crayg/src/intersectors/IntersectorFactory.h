#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_

#include "SceneIntersector.h"
#include "BvhBuilder.h"
#include "BvhSceneIntersector.h"
namespace crayg {

class IntersectorFactory {
 public:
    static std::shared_ptr<SceneIntersector> createSceneIntersector(const IntersectorType &integratorType,
                                                                    Scene &scene) {
        switch (integratorType) {
            case IntersectorType::NAIVE_BVH:return createNaiveBvh(scene);
            default:
                throw std::runtime_error(fmt::format(R"(Unsupported Intersector type: "{}")",
                                                     magic_enum::enum_name(integratorType)));
        }
    }
    static std::shared_ptr<SceneIntersector> createNaiveBvh(Scene &scene) {
        BvhBuilder bvhBuilder(scene);
        auto bvh = bvhBuilder.build();
        return std::make_shared<BvhSceneIntersector>(scene, std::move(bvh));
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_
