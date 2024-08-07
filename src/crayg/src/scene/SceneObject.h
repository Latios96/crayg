#pragma once

#include "Imageable.h"
#include "Transformable.h"
#include <vector>

namespace crayg {

class SceneObject : public Imageable, public Transformable {
  public:
    SceneObject();

    explicit SceneObject(Vector3f position);
    virtual ~SceneObject() = default;

    const std::string &getName() const;
    void setName(const std::string &name);
    virtual std::string getType() = 0;
    virtual void getPrimitives(std::vector<Imageable *> &target) const;
    virtual std::size_t primitiveCount() const;

  private:
    std::string name;
};

}
