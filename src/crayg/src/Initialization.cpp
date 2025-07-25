#include "Initialization.h"

#include <ImfThreading.h>
#include <cpuinfo.h>
#include <thread>

namespace crayg {

bool Initialization::isInitialized = false;

void Initialization::initialize() {
    InitializationOptions initializationOptions{};
    initialize(initializationOptions);
}

void Initialization::initialize(const InitializationOptions &options) {
    if (isInitialized) {
        return;
    }

    Imf::setGlobalThreadCount(options.openExrThreadCount.getThreadCount());

    cpuinfo_initialize();

    isInitialized = true;
}

}