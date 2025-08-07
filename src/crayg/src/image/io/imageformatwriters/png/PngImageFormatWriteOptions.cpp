#include "PngImageFormatWriteOptions.h"
#include "utils/ToStringHelper.h"

namespace crayg {

std::ostream &operator<<(std::ostream &os, const crayg::PngImageFormatWriteOptions &options) {
    os << ToStringHelper("PngImageFormatWriteOptions").finish();
    return os;
}
}