#ifndef CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_

#include <string>
#include <vector>
#include "TestPattern.h"

namespace knipser {

class TestPatternStringParser {
 public:
    explicit TestPatternStringParser(std::string parseString);
    std::vector<TestPattern> parse() const;
 private:
    std::string parseString;
};

}

#endif //CRAYG_SRC_KNIPSER_SRC_TESTPATTERNSTRINGPARSER_H_
