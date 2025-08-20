#include "LodePNG_formatter.h"

std::ostream &operator<<(std::ostream &os, const LodePNGColorType &value) {
    os << magic_enum::enum_name(value);
    return os;
}