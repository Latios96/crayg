#ifndef CRAYG_SRC_CRAYG_SRC_CRAYGINFO_H_
#define CRAYG_SRC_CRAYG_SRC_CRAYGINFO_H_

#include <string>
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "0000000" // 0000000 means uninitialized
#endif

namespace crayg {

class CraygInfo {
  public:
    static std::string const VERSION;
    static std::string const COMMIT_HASH;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_CRAYGINFO_H_
