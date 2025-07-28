#include "EmbreeBvh.h"

namespace crayg {
EmbreeBvh::~EmbreeBvh() {
    rtcReleaseScene(rtcScene);
    rtcReleaseDevice(rtcDevice);
}
}