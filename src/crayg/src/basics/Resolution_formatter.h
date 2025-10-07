#pragma once

#include "Resolution.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Resolution> : ostream_formatter {};
