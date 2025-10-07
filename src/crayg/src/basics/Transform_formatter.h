#pragma once

#include "Transform.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Transform> : ostream_formatter {};
