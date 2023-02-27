#ifndef CRAYG_TEMPORARYDIRECTORY_H
#define CRAYG_TEMPORARYDIRECTORY_H

#include <boost/filesystem.hpp>

namespace crayg {

class TemporaryDirectory {
  public:
    TemporaryDirectory();
    const boost::filesystem::path &getPath() const;
    virtual ~TemporaryDirectory();

  private:
    boost::filesystem::path path;
};

} // crayg

#endif // CRAYG_TEMPORARYDIRECTORY_H
