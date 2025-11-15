#include "Bound2d.h"
#include "Vector2_formatter.h"
#include "crayg/foundation/objects/ToStringHelper.h"

namespace crayg {

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Bounds2df, min, max);
CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Bounds2di, min, max);

}
