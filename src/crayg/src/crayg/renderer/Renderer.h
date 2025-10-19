#pragma once

#include "TileStats.h"
#include "crayg/foundation/areaiterators/tiles/tilequeues/TileQueue.h"
#include "crayg/foundation/math/geometry/Color.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/progress/TaskReporter.h"
#include "crayg/image/Image.h"
#include "crayg/renderer/intersectors/SceneIntersector.h"
#include "crayg/renderer/outputdrivers/NextGenOutputDriver.h"
#include "crayg/scene/RenderSettings.h"
#include "crayg/scene/Scene.h"
#include "crayg/scene/camera/Camera.h"
#include "crayg/scene/camera/pinhole/PinholeCameraModel.h"
#include "integrators/AbstractIntegrator.h"
#include "tilesamplers/TileSampler.h"

namespace crayg {

class Renderer {
  public:
    Renderer(Scene &scene, NextGenOutputDriver &outputDriver, BaseTaskReporter &taskReporter, TileQueue &tileQueue);

    void initOutputDriver();
    void renderScene();

  private:
    Scene &scene;
    NextGenOutputDriver &outputDriver;
    std::unique_ptr<CameraModel> cameraModel;
    std::shared_ptr<SceneIntersector> sceneIntersector;
    BaseTaskReporter &taskReporter;
    TileQueue &tileQueue;
    std::vector<Tile> tileSequence;

    TileStats tileStats;

    void init();
    void initTiles();

    void renderSerial(BaseTaskReporter::TaskProgressController &taskProgressController);
    void renderParallel(BaseTaskReporter::TaskProgressController &taskProgressController);
    void renderTile(const Tile &tile);
    Color renderSample(const Vector2f &samplePos);
    Color renderSample(const Vector2f &samplePos, float waveLength);

    std::unique_ptr<AbstractIntegrator> integrator;
    std::unique_ptr<TileSampler> tileSampler;

    void writeImageMetadata(std::chrono::seconds renderTime);
    ImageSpec requiredImageSpec(const Resolution &resolution) const;
};

}
