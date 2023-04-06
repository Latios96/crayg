#include "TemporaryDirectory.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace crayg {

TemporaryDirectory::TemporaryDirectory() {
    path = boost::filesystem::temp_directory_path() / boost::uuids::to_string(boost::uuids::random_generator()());
    boost::filesystem::create_directories(path);
}

TemporaryDirectory::~TemporaryDirectory() {
    boost::filesystem::remove_all(path);
}

const boost::filesystem::path &TemporaryDirectory::getPath() const {
    return path;
}

std::string TemporaryDirectory::writeToFile(const std::string &fileName, const std::string &content) {
    const std::string &filePath = (path / fileName).string();
    std::ofstream o(filePath);
    o << content;
    o.close();
    return filePath;
}

} // crayg