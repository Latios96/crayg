#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_TRACING_CRAYGTRACING_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_TRACING_CRAYGTRACING_H_

#define CRG_EMPTY_TRACE                                                                                                \
    do {                                                                                                               \
    } while (false)

#ifdef CRAYG_ENABLE_TRACING

#include "minitrace.h"

#define CRG_TRACE_SCOPE(c) MTR_SCOPE(c, __FUNCTION__)
#define CRG_IF_TRACE(s) s

#else

#define CRG_TRACE_SCOPE(c) CRG_EMPTY_TRACE
#define CRG_IF_TRACE(s) CRG_EMPTY_TRACE

#endif

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_TRACING_CRAYGTRACING_H_
