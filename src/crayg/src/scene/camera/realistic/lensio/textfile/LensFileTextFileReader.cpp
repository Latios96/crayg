#include "LensFileTextFileReader.h"
#include "utils/utils.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <regex>
#include <sstream>

namespace crayg {

bool lineIsSingleInteger(const std::string &line) {
    static const std::regex txt_regex("\\d+");
    return std::regex_match(line, txt_regex);
}

CameraLens LensFileTextFileReader::readFileContent(const std::string &content) {
    std::vector<LensElement> elements;
    std::vector<std::string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));

    bool hasSeenLensCount = false;
    for (auto &line : lines) {
        line = stripCommentFromLine(line);
        if (line.empty()) {
            continue;
        }
        if (!hasSeenLensCount && lineIsSingleInteger(line)) {
            hasSeenLensCount = true;
            continue;
        }
        elements.push_back(readLensElement(line));
    }

    return {CameraLensMetadata(), elements};
}

LensElement LensFileTextFileReader::readLensElement(const std::string &line) const {
    std::istringstream iss(line);

    float radius, thickness, ior, diameter;
    iss >> radius;
    iss >> thickness;
    iss >> ior;
    iss >> diameter;

    return {radius * 0.1f, thickness * 0.1f, ior, diameter / 2.f * 0.1f};
}

} // crayg