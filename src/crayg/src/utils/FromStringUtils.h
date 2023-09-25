#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_FROMSTRINGUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_FROMSTRINGUTILS_H_

namespace crayg {

class FromStringUtils {
  public:
    static int parseIntOrThrow(const std::string &str);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_FROMSTRINGUTILS_H_
