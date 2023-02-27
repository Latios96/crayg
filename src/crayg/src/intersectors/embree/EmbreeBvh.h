#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_

#include "utils/DtoUtils.h"
#include <embree3/rtcore.h>
#include <unordered_map>

namespace crayg {

enum EmbreePrimitiveType { TRIANGLE_MESH, SUBDIVISION_SURFACE_MESH, SPHERE };

CRAYG_DTO_2(EmbreeMappingEntry, std::uint32_t, sceneObjectIndex, EmbreePrimitiveType, primitiveType)

struct EmbreeBvh {
    RTCDevice rtcDevice;
    RTCScene rtcScene;
    std::unordered_map<unsigned int, EmbreeMappingEntry> geomIdToSceneObject;
    virtual ~EmbreeBvh();
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
