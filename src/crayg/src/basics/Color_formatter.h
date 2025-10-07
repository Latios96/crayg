#pragma once

#include "Color.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Color> : ostream_formatter {};
