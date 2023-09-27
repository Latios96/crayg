#ifndef CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
#define CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_

#include "Logger.h"
#include <basics/Vector3f.h>
#include <fmt/format.h>
#include <stdexcept>

#define CRAYG_CHECK_IS_NORMALIZED_VECTOR(vector) CRAYG_CHECK_IS_NORMALIZED_VECTOR_IMPL(vector)
#define CRAYG_CHECK_IS_VALID_INDEX(index, size) CRAYG_CHECK_IS_VALID_INDEX_IMPL(index, size)

#ifdef CRAYG_DEBUG_CHECKS
#define CRAYG_CHECKD_IS_NORMALIZED_VECTOR(vector) CRAYG_CHECK_IS_NORMALIZED_VECTOR_IMPL(vector)
#define CRAYG_CHECKD_IS_VALID_INDEX(index, size) CRAYG_CHECK_IS_VALID_INDEX_IMPL(index, size)
#else
#define CRAYG_CHECKD_IS_NORMALIZED_VECTOR(vector) EMPTY_CHECK
#define CRAYG_CHECKD_IS_VALID_INDEX(index, size) EMPTY_CHECK
#endif

#define CRAYG_CHECK_IS_NORMALIZED_VECTOR_IMPL(vector)                                                                  \
    CRAYG_CHECK_OR_THROW(fabs((vector).length() - 1) < 0.001, fmt::format("Vector is not unit vector!: {}", vector))

#define CRAYG_CHECK_IS_VALID_INDEX_IMPL(index, size)                                                                   \
    CRAYG_CHECK_OR_THROW((index >= 0 && index < size),                                                                 \
                         fmt::format("Index is out of range: {}, size is {}", index, size))

#define CRAYG_CHECK_OR_THROW(condition, message)                                                                       \
    if (!(condition)) {                                                                                                \
        CRAYG_LOG_AND_THROW(message)                                                                                   \
    }

#define EMPTY_CHECK                                                                                                    \
    do {                                                                                                               \
    } while (false)

#endif // CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
