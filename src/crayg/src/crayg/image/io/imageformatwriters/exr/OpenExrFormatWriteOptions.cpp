#include "OpenExrFormatWriteOptions.h"
#include "crayg/compatibility/openexr/fmt/ImfCompression_formatter.h"
#include "crayg/compatibility/openexr/fmt/ImfPixelType_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(OpenExrFormatWriteOptions, compression, pixelType, openExrDataWindow);

bool OpenExrFormatWriteOptions::operator==(const OpenExrFormatWriteOptions &rhs) const {
    return compression == rhs.compression && pixelType == rhs.pixelType && openExrDataWindow == rhs.openExrDataWindow;
}

bool OpenExrFormatWriteOptions::operator!=(const OpenExrFormatWriteOptions &rhs) const {
    return !(rhs == *this);
}

}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::OpenExrDataWindow);
