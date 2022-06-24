#include "ExecuteTestPredicate.h"

#include <utility>

namespace knipser {

ExecuteTestPredicate::ExecuteTestPredicate(std::vector<TestPattern> testPatterns)
    : testPatterns(std::move(testPatterns)) {}
bool ExecuteTestPredicate::shouldExecute(const KnipserTest &test) {
    if (testPatterns.empty()) {
        return true;
    }
    for (auto &testPattern : testPatterns) {
        if (testPattern.matches(test.name)) {
            return true;
        }
    }
    return false;
}

}
