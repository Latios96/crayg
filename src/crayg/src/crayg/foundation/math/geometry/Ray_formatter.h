#pragma once

#include "Ray.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Ray> : ostream_formatter {};
