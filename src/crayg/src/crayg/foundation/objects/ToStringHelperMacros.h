#pragma once

#include "ToStringHelper.h"
#include "crayg/foundation/macros/ForeachVararg.h"

#define CRAYG_TO_STRING_HELPER_ADD_MEMBER(member) .addMember(#member, obj.member)

#define CRAYG_TO_STRING_HELPER(os, Type, ...)                                                                          \
    ToStringHelper2(os, #Type) CRAYG_FOREACH_VARARG(CRAYG_TO_STRING_HELPER_ADD_MEMBER, __VA_ARGS__).finish()
#define CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Type, ...)                                                                 \
    std::ostream &operator<<(std::ostream &os, const Type &obj) {                                                      \
        return CRAYG_TO_STRING_HELPER(os, Type, __VA_ARGS__);                                                          \
    }
