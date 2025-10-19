#pragma once

#include "BoundingBox.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::BoundingBox> : ostream_formatter {};
