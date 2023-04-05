#include "LensFileReader.h"

namespace crayg {

LensFileReader::LensFileReader(const std::string &filePath) : filePath(filePath) {
}

std::vector<LensElement> LensFileReader::readFile() {
    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return readFileContent(buffer.str());
}

}