#pragma once

#include "Vector3f.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Vector3f> : ostream_formatter {};
