#include "ImfPixelType_formatter.h"
#include <magic_enum.hpp>

namespace std {

std::ostream &operator<<(std::ostream &os, Imf::PixelType value) {
    os << magic_enum::enum_name(value);
    return os;
}

}
