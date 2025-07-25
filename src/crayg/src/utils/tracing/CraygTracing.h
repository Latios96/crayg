#pragma once

#define CRAYG_EMPTY_TRACE                                                                                              \
    do {                                                                                                               \
    } while (false)

#ifdef CRAYG_ENABLE_TRACING

#include "external/minitrace/minitrace.h"

#define CRAYG_TRACE_SCOPE(c) MTR_SCOPE(c, __FUNCTION__)
#define CRG_IF_TRACING_ENABLED(s) s

#else

#define CRAYG_TRACE_SCOPE(c) CRAYG_EMPTY_TRACE
#define CRAYG_IF_TRACING_ENABLED(s) CRAYG_EMPTY_TRACE

#endif
