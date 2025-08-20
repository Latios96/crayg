#pragma once
#include "ImfCompression_formatter.h"
#include <magic_enum.hpp>

namespace std {

std::ostream &operator<<(std::ostream &os, Imf::Compression value) {
    os << magic_enum::enum_name(value);
    return os;
}

}
