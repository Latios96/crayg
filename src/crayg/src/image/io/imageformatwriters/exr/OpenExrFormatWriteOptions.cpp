#include "OpenExrFormatWriteOptions.h"
#include "compatibility/openexr/fmt/ImfCompression_formatter.h"
#include "compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "utils/ToStringHelper.h"

namespace crayg {

std::ostream &operator<<(std::ostream &os, const OpenExrFormatWriteOptions &options) {
    os << ToStringHelper("OpenExrFormatWriteOptions")
              .addMember("compression", options.compression)
              .addMember("pixelType", options.pixelType)
              .addMember("openExrDataWindow", options.openExrDataWindow)
              .finish();
    return os;
}

}
