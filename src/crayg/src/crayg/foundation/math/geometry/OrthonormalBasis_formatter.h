#pragma once

#include "Vector3f.h"
#include <fmt/ostream.h>
#include <ostream>

template <> struct fmt::formatter<crayg::OrthonormalBasis> : ostream_formatter {};
