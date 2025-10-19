#pragma once

#include "Bound2d.h"
#include "Vector2_formatter.h"
#include <fmt/ostream.h>

template <typename T> struct fmt::formatter<crayg::Bounds2d<T>> : ostream_formatter {};
