#include "ThreadCount.h"
#include <thread>

namespace crayg {

int ThreadCount::getThreadCount() const {
    if (count > 0) {
        return count;
    }
    return std::thread::hardware_concurrency() + count;
}

}