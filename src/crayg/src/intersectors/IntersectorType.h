#ifndef CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_
#define CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_

#include "utils/EnumUtils.h"
#include <fmt/format.h>

namespace crayg {

enum class IntersectorType { EMBREE = 2 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::IntersectorType);

#endif // CRAYG_SRC_CRAYG_SRC_INTERSECTORS_INTERSECTORTYPE_H_
