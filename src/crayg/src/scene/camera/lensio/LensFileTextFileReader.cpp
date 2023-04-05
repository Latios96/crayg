#include "LensFileTextFileReader.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/filesystem.hpp>

namespace crayg {

LensFileTextFileReader::LensFileTextFileReader(const std::string &filePath) : LensFileReader(filePath) {
}

std::string stripCommentFromLine(std::string line) {
    auto commentPosition = line.find('#');
    if (commentPosition != std::string::npos) {
        line = line.substr(0, commentPosition);
    }
    boost::algorithm::trim_all(line);
    return line;
}

std::vector<LensElement> LensFileTextFileReader::readFileContent(const std::string &content) {
    std::vector<LensElement> elements;
    std::vector<std::string> lines;
    boost::split(lines, content, boost::is_any_of("\n"));

    bool hasSeenLensCount = false;
    for (auto &line : lines) {
        line = stripCommentFromLine(line);
        if (line.empty()) {
            continue;
        }
        if (!hasSeenLensCount) {
            hasSeenLensCount = true;
            continue;
        }
        elements.push_back(readLensElement(line));
    }

    return elements;
}

LensElement LensFileTextFileReader::readLensElement(const std::string &line) const {
    std::istringstream iss(line);

    float radius, thickness, ior, diameter;
    iss >> radius;
    iss >> thickness;
    iss >> ior;
    iss >> diameter;

    return {radius, thickness, ior, diameter};
}

} // crayg