//
// Created by Jan Honsbrok on 09.01.20.
//

#include "TestPatternStringParser.h"

#include <utility>
#include <sstream>

TestPatternStringParser::TestPatternStringParser(std::string parseString) : parseString(std::move(parseString)) {}

std::vector<TestPattern> TestPatternStringParser::parse() const {
    std::vector<TestPattern> patterns;
    std::string token;
    std::istringstream tokenStream(parseString);
    while (std::getline(tokenStream, token, ',')) {
        token = trim(token);
        if (!token.empty()) {
            patterns.emplace_back(token);
        }
    }
    return patterns;
}
std::string TestPatternStringParser::trim(const std::string &s) const {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}
