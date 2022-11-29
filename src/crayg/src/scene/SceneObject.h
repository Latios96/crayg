#ifndef CRAYG_SCENEOBJECT_H
#define CRAYG_SCENEOBJECT_H

#include "Transformable.h"
#include "Imageable.h"

namespace crayg {

class SceneObject : public Imageable,
                    public Transformable {
 public:
    SceneObject();

    explicit SceneObject(Vector3f position);
    virtual ~SceneObject() = default;

    const std::string &getName() const;
    void setName(const std::string &name);
    virtual std::string getType() = 0;
    virtual void getPrimitives(std::vector<Imageable *> &target, bool *isOwning);
 private:
    std::string name;
};

}

#endif //CRAYG_SCENEOBJECT_H
