#pragma once

#include "Preconditions.normal.generated.h"

#ifdef CRAYG_DEBUG_BUILD
#define CRAYG_DEBUG_CHECKS
#endif

#ifdef CRAYG_DEBUG_CHECKS

#include "Exceptions.h"
#include <fmt/format.h>

#include "Preconditions.debug.generated.h"

#else
#include "Preconditions.debugdisabled.generated.h"
#endif

#include "Preconditions.impls.generated.h"

#define CRAYG_CHECK_OR_THROW(condition, message)                                                                       \
    if (!(condition)) {                                                                                                \
        CRAYG_LOG_AND_THROW_MESSAGE(message)                                                                           \
    }

#define CRAYG_EMPTY_CHECK                                                                                              \
    do {                                                                                                               \
    } while (false)
