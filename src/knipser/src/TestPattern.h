//
// Created by Jan Honsbrok on 09.01.20.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_TESTPATTERN_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTPATTERN_H_

#include <string>

class TestPattern {
 public:
    explicit TestPattern(std::string pattern);
    const std::string pattern;

    bool matches(const std::string &testName) const;
};

#endif //CRAYG_SRC_KNIPSER_SRC_TESTPATTERN_H_
