#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_

#include <embree3/rtcore.h>
#include <unordered_map>

namespace crayg {

enum EmbreePrimitiveType{
    TRIANGLE_MESH,
    SPHERE
};

struct EmbreeBvh {
    RTCDevice rtcDevice;
    RTCScene rtcScene;
    std::unordered_map<unsigned int, std::pair<unsigned int, EmbreePrimitiveType>> geomIdToSceneObject;
    virtual ~EmbreeBvh();
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
