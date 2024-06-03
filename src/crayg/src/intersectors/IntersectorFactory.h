#pragma once

#include "SceneIntersector.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"
#include "intersectors/embree/EmbreeSceneIntersector.h"
#include "utils/Exceptions.h"

namespace crayg {

class IntersectorFactory {
  public:
    static std::shared_ptr<SceneIntersector> createSceneIntersector(const IntersectorType &intersectorType,
                                                                    Scene &scene) {
        switch (intersectorType) {
        case IntersectorType::EMBREE:
            return createEmbreeBvh(scene);
        default:
            CRAYG_LOG_AND_THROW(
                std::runtime_error(fmt::format(R"(Unsupported Intersector type: "{}")", intersectorType)));
        }
    }

    static std::shared_ptr<SceneIntersector> createEmbreeBvh(Scene &scene) {
        EmbreeBvhBuilder embreeBvhBuilder(scene);
        auto bvh = embreeBvhBuilder.build();
        return std::make_shared<EmbreeSceneIntersector>(scene, std::move(bvh));
    }
};

} // crayg
