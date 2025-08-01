#include "TemporaryDirectory.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <fstream>

namespace crayg {

TemporaryDirectory::TemporaryDirectory() {
    path = std::filesystem::temp_directory_path() / boost::uuids::to_string(boost::uuids::random_generator()());
    std::filesystem::create_directories(path);
}

TemporaryDirectory::~TemporaryDirectory() {
    std::filesystem::remove_all(path);
}

const std::filesystem::path TemporaryDirectory::getPath() const {
    return path;
}

std::string TemporaryDirectory::writeToFile(const std::string &fileName, const std::string &content) {
    const std::string &filePath = getFilePath(fileName);
    std::ofstream o(filePath);
    o << content;
    o.close();
    return filePath;
}

const std::string TemporaryDirectory::getFilePath(const std::string &fileName) const {
    return (path / fileName).string();
}

}