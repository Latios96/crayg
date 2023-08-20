#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_

#include <basics/Color.h>

#include <functional>
#include <utility>

namespace crayg {

class ShadingNode {
  public:
    ShadingNode();
    explicit ShadingNode(std::string name);
    std::string getName() const;
    virtual std::string getType() = 0;

  private:
    std::string name;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_SHADINGNODE_H_
