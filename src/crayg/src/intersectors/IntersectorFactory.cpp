#include "IntersectorFactory.h"
#include "intersectors/embree/EmbreeBvhBuilder.h"
#include "intersectors/embree/EmbreeSceneIntersector.h"
#include "utils/Exceptions.h"

namespace crayg {

std::shared_ptr<SceneIntersector> IntersectorFactory::createSceneIntersector(const IntersectorType &intersectorType,
                                                                             Scene &scene) {
    switch (intersectorType) {
    case IntersectorType::EMBREE:
        return createEmbreeBvh(scene);
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR(R"(Unsupported Intersector type: "{}")", intersectorType);
    }
}

std::shared_ptr<SceneIntersector> IntersectorFactory::createEmbreeBvh(Scene &scene) {
    EmbreeBvhBuilder embreeBvhBuilder(scene);
    auto bvh = embreeBvhBuilder.build();
    return std::make_shared<EmbreeSceneIntersector>(scene, std::move(bvh));
}

}
