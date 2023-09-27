#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_

#define CRAYG_LOG_AND_THROW(exception)                                                                                 \
    Logger::error("Error at {}:{}: {}", __FILE__, __LINE__, (exception.what()));                                       \
    throw(exception);

#define CRAYG_LOG_AND_THROW_MESSAGE(message) CRAYG_LOG_AND_THROW(std::runtime_error(message))

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
