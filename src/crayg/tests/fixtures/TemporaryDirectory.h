#ifndef CRAYG_TEMPORARYDIRECTORY_H
#define CRAYG_TEMPORARYDIRECTORY_H

#include <boost/filesystem.hpp>

namespace crayg {

class TemporaryDirectory {
  public:
    TemporaryDirectory();
    const boost::filesystem::path getPath() const;
    const std::string getFilePath(const std::string &fileName) const;
    std::string writeToFile(const std::string &fileName, const std::string &content);
    virtual ~TemporaryDirectory();

  private:
    boost::filesystem::path path;
};

} // crayg

#endif // CRAYG_TEMPORARYDIRECTORY_H
