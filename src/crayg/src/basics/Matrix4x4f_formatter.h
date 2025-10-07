#pragma once

#include "Matrix4x4f.h"
#include <fmt/ostream.h>

template <> struct fmt::formatter<crayg::Matrix4x4f> : ostream_formatter {};
