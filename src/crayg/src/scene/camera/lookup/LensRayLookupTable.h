#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUP_LENSRAYLOOKUPTABLE_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUP_LENSRAYLOOKUPTABLE_H_

#include "basics/Resolution.h"
#include "basics/Vector3f.h"
#include "image/ImageBucket.h"
#include "scene/camera/Camera.h"
#include "scene/camera/CameraModel.h"
#include <vector>

namespace crayg {

class LensRayLookupTable {
  public:
    LensRayLookupTable(const Resolution &resolution, int samplesPerPixel, bool useSpectralLensing);

    void generate(CameraModel &cameraModel);

    void write(const std::string &path);
    void read(const std::string &path);
    std::vector<Ray> rays; // todo also store position on lens..
    Resolution resolution;
    int samplesPerPixel;
    bool useSpectralLensing;
    void sampleImageBucket(CameraModel &cameraModel, crayg::ImageBucket &imageBucket);

    int getVec3fIndex(const Vector2i &pixel, int sampleNumber, int offsetInRay);
    Ray getRay(const Vector2i &pixel, int sampleNumber);
    void storeRay(const std::optional<Ray> &ray, const Vector2i &pixel, int sampleNumber, int waveLengthIndex);
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LOOKUP_LENSRAYLOOKUPTABLE_H_