#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_

#include "SceneIntersector.h"
#include "naive/NaiveBvhBuilder.h"
#include "naive/NaiveBvhSceneIntersector.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"
#include "intersectors/embree/EmbreeSceneIntersector.h"
namespace crayg {

class IntersectorFactory {
 public:
    static std::shared_ptr<SceneIntersector> createSceneIntersector(const IntersectorType &integratorType,
                                                                    Scene &scene) {
        switch (integratorType) {
            case IntersectorType::NAIVE_BVH:return createNaiveBvh(scene);
            case IntersectorType::EMBREE:return createEmbreeBvh(scene);
            default:
                throw std::runtime_error(fmt::format(R"(Unsupported Intersector type: "{}")",
                                                     magic_enum::enum_name(integratorType)));
        }
    }
    static std::shared_ptr<SceneIntersector> createNaiveBvh(Scene &scene) {
        NaiveBvhBuilder bvhBuilder(scene);
        auto bvh = bvhBuilder.build();
        return std::make_shared<NaiveBvhSceneIntersector>(scene, std::move(bvh));
    }
    static std::shared_ptr<SceneIntersector> createEmbreeBvh(Scene &scene) {
        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto bvh = embreeBvhBuilder.build();
        return std::make_shared<EmbreeSceneIntersector>(scene, std::move(bvh));
    }
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORFACTORY_H_
