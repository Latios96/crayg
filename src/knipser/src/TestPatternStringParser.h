//
// Created by Jan Honsbrok on 09.01.20.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_

#include <string>
#include <vector>
#include "TestPattern.h"

class TestPatternStringParser {
 public:
    explicit TestPatternStringParser(std::string parseString);
    std::vector<TestPattern> parse() const;
 private:
    std::string parseString;
    std::string trim(const std::string &s) const;
};

#endif //CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_
