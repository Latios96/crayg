#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_

#include <embree3/rtcore.h>
#include <unordered_map>
#include "utils/PairDto.h"

namespace crayg {

enum EmbreePrimitiveType {
    TRIANGLE_MESH,
    SUBDIVISION_SURFACE_MESH,
    SPHERE
};

CRAYG_PAIR_DTO(EmbreeMappingEntry,unsigned int,sceneObjectIndex,EmbreePrimitiveType,primitiveType)

struct EmbreeBvh {
    RTCDevice rtcDevice;
    RTCScene rtcScene;
    std::unordered_map<unsigned int, EmbreeMappingEntry> geomIdToSceneObject;
    virtual ~EmbreeBvh();
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
