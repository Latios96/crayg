#include "EmbreeBvh.h"

namespace crayg {
EmbreeBvh::~EmbreeBvh() {
    rtcReleaseScene(rtcScene);
    rtcReleaseDevice(rtcDevice);
}
}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::EmbreePrimitiveType);
