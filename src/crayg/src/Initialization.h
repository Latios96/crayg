#pragma once
#include "crayg/foundation/parallel/ThreadCount.h"

namespace crayg {

struct InitializationOptions {
    ThreadCount openExrThreadCount;
};

class Initialization {
  public:
    static void initialize();
    static void initialize(const InitializationOptions &options);

  private:
    static bool isInitialized;
};

}