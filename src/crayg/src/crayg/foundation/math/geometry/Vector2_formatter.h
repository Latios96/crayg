#pragma once

#include "Vector2.h"
#include <fmt/ostream.h>
#include <ostream>

template <typename T> struct fmt::formatter<crayg::Vector2<T>> : ostream_formatter {};
