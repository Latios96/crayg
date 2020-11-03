//
// Created by Jan Honsbrok on 09.01.20.
//

#include "TestPatternStringParser.h"

#include <utility>
#include <sstream>
#include <boost/algorithm/string.hpp>

TestPatternStringParser::TestPatternStringParser(std::string parseString) : parseString(std::move(parseString)) {}

std::vector<TestPattern> TestPatternStringParser::parse() const {
    std::vector<std::string> splitResults;
    boost::algorithm::split(splitResults, parseString, boost::algorithm::is_any_of(","));

    std::vector<TestPattern> patterns;
    for (auto &patternString : splitResults) {
        patternString = boost::algorithm::trim_copy(patternString);
        if (!patternString.empty()) {
            patterns.emplace_back(patternString);
        }
    }
    return patterns;
}

