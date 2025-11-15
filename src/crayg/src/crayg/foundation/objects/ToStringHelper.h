#pragma once

#include "crayg/foundation/macros/ForeachVararg.h"
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <string>

namespace crayg {

class ToStringHelper {
  public:
    explicit ToStringHelper(std::ostream &os, const std::string_view &className) : os(os) {
        os << className << '{';
    }

    template <typename T> ToStringHelper &addMember(const std::string_view &name, const T &value) {
        if (hasMembers) {
            os << ',';
        }

        fmt::print(os, "{}={}", name, value);

        hasMembers = true;
        return *this;
    };

    std::ostream &finish() const {
        os << '}';
        return os;
    }

  private:
    std::ostream &os;
    bool hasMembers = false;
};

}

#define CRAYG_TO_STRING_HELPER_ADD_MEMBER(member) .addMember(#member, obj.member)

#define CRAYG_TO_STRING_HELPER(os, Type, ...)                                                                          \
    ToStringHelper(os, #Type) CRAYG_FOREACH_VARARG(CRAYG_TO_STRING_HELPER_ADD_MEMBER, __VA_ARGS__).finish()

#define CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Type, ...)                                                                 \
    std::ostream &operator<<(std::ostream &os, const Type &obj) {                                                      \
        return CRAYG_TO_STRING_HELPER(os, Type, __VA_ARGS__);                                                          \
    }
