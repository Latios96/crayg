//
// Created by Jan Honsbrok on 10.01.20.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_EXECUTETESTPREDICATE_H_
#define CRAYG_SRC_KNIPSER_SRC_EXECUTETESTPREDICATE_H_

#include <vector>
#include "TestPattern.h"
#include "KnipserTest.h"

namespace knipser {

class ExecuteTestPredicate {
 public:
    explicit ExecuteTestPredicate(std::vector<TestPattern> testPatterns);

    bool shouldExecute(const KnipserTest &test);
 private:
    const std::vector<TestPattern> testPatterns;
};

}

#endif //CRAYG_SRC_KNIPSER_SRC_EXECUTETESTPREDICATE_H_
