#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_

#include "ShadingNode.h"
#include "integrators/SurfaceInteraction.h"
#include <basics/Color.h>
#include <basics/Ray.h>

namespace crayg {

class Material : public ShadingNode {
 public:
    explicit Material();
    explicit Material(const std::string &name);
    virtual Color evaluate(const SurfaceInteraction &surfaceInteraction) = 0;
    virtual std::string getType() = 0;
    void connectOutputToInput(const std::string &inputPlugName, PlugPtr outputPlug) override;
    PlugPtr getPlugByName(const std::string &inputPlugName) override;
};

} // namespace crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_MATERIAL_H_
