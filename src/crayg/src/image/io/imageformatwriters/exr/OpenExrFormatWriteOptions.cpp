#include "OpenExrFormatWriteOptions.h"
#include "compatibility/openexr/fmt/ImfCompression_formatter.h"
#include "compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

std::ostream &operator<<(std::ostream &os, const OpenExrFormatWriteOptions &options) {
    os << ToStringHelper("OpenExrFormatWriteOptions")
              .addMember("compression", options.compression)
              .addMember("pixelType", options.pixelType)
              .addMember("openExrDataWindow", options.openExrDataWindow)
              .finish();
    return os;
}

bool OpenExrFormatWriteOptions::operator==(const OpenExrFormatWriteOptions &rhs) const {
    return compression == rhs.compression && pixelType == rhs.pixelType && openExrDataWindow == rhs.openExrDataWindow;
}

bool OpenExrFormatWriteOptions::operator!=(const OpenExrFormatWriteOptions &rhs) const {
    return !(rhs == *this);
}

}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::OpenExrDataWindow);
