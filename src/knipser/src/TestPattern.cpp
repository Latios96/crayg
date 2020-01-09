//
// Created by Jan Honsbrok on 09.01.20.
//

#include "TestPattern.h"

#include <utility>
#include <regex>

TestPattern::TestPattern(std::string pattern) : pattern(std::move(pattern)) {}

bool TestPattern::matches(const std::string &testName) const {
    std::regex re(pattern, std::regex_constants::icase);
    std::smatch match;
    return match[0].matched && match[0].length() == testName.size();
}
bool TestPattern::operator==(const TestPattern &rhs) const {
    return pattern == rhs.pattern;
}
bool TestPattern::operator!=(const TestPattern &rhs) const {
    return !(rhs == *this);
}
std::ostream &operator<<(std::ostream &os, const TestPattern &pattern) {
    os << "pattern: \"" << pattern.pattern << "\"" ;
    return os;
}
