#pragma once

#include <filesystem>

namespace crayg {

class TemporaryDirectory {
  public:
    TemporaryDirectory();
    const std::filesystem::path getPath() const;
    const std::string getFilePath(const std::string &fileName) const;
    std::string writeToFile(const std::string &fileName, const std::string &content);
    virtual ~TemporaryDirectory();

  private:
    std::filesystem::path path;
};

} // crayg
