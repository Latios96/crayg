#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_

#include <embree3/rtcore.h>
#include <unordered_map>

namespace crayg {

struct EmbreeBvh {
    RTCDevice rtcDevice;
    RTCScene rtcScene;
    std::unordered_map<unsigned int, unsigned int> geomIdToSceneObject;
    virtual ~EmbreeBvh();
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_INTERSECTORS_EMBREE_EMBREEBVH_H_
