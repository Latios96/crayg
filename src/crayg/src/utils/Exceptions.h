#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_

#define CRAYG_LOG_AND_THROW(message)                                                                                   \
    Logger::error("Error at {}:{}: {}", __FILE__, __LINE__, message);                                                  \
    throw std::runtime_error(fmt::format("Error at {}:{}: {}", __FILE__, __LINE__, message));

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_EXCEPTIONS_H_
