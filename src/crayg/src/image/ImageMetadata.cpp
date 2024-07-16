#include "ImageMetadata.h"

namespace crayg {

const std::string ImageMetadataTokens::RENDER_TIME = "crayg/info/time";
const std::string ImageMetadataTokens::RENDER_TIME_SECONDS = "crayg/info/time/seconds";
const std::string ImageMetadataTokens::CRAYG_VERSION = "crayg/info/craygVersion";
const std::string ImageMetadataTokens::COMPUTER_NAME = "crayg/info/computerName";
const std::string ImageMetadataTokens::CPU = "crayg/info/cpu";
const std::string ImageMetadataTokens::RENDER_SETTINGS_INTEGRATOR = "crayg/renderSettings/integrator";
const std::string ImageMetadataTokens::RENDER_SETTINGS_INTERSECTOR = "crayg/renderSettings/intersector";
const std::string ImageMetadataTokens::RENDER_SETTINGS_MAX_SAMPLES = "crayg/renderSettings/maxSamples";
const std::string ImageMetadataTokens::RENDER_SETTINGS_BUCKET_SEQUENCE_TYPE = "crayg/renderSettings/bucketSequenceType";
const std::string ImageMetadataTokens::RENDER_SETTINGS_BUCKET_SAMPLER_TYPE = "crayg/renderSettings/bucketSamplerType";
const std::string ImageMetadataTokens::RENDER_SETTINGS_ADAPTIVE_MAX_ERROR = "crayg/renderSettings/adaptiveMaxError";
const std::string ImageMetadataTokens::RENDER_SETTINGS_SAMPLES_PER_ADAPTIVE_PASS =
    "crayg/renderSettings/samplesPerAdaptivePass";
const std::string ImageMetadataTokens::RENDER_SETTINGS_USE_SPECTRAL_LENSING = "crayg/renderSettings/useSpectralLensing";
const std::string ImageMetadataTokens::RENDER_SETTINGS_REGION_TO_RENDER = "crayg/renderSettings/regionToRender";
const std::string ImageMetadataTokens::CAMERA_NAME = "crayg/camera/name";
const std::string ImageMetadataTokens::CAMERA_FOCAL_LENGTH = "crayg/camera/focalLength";
const std::string ImageMetadataTokens::CAMERA_FILM_BACK_SIZE = "crayg/camera/filmBackSize";
const std::string ImageMetadataTokens::CAMERA_FOCUS_DISTANCE = "crayg/camera/focusDistance";
const std::string ImageMetadataTokens::CAMERA_F_STOP = "crayg/camera/fStop";
const std::string ImageMetadataTokens::CAMERA_CAMERA_TYPE = "crayg/camera/cameraType";
const std::string ImageMetadataTokens::CAMERA_LENS_NAME = "crayg/camera/lens/name";
const std::string ImageMetadataTokens::CAMERA_LENS_SURFACE_COUNT = "crayg/camera/lens/surfaceCount";
const std::string ImageMetadataTokens::CAMERA_LENS_EFFECTIVE_FOCAL_LENGTH = "crayg/camera/lens/effectiveFocalLength";
const std::string ImageMetadataTokens::CAMERA_LENS_MAXIMUM_F_NUMBER = "crayg/camera/lens/maximumfnumber";
const std::string ImageMetadataTokens::CAMERA_LENS_IS_ANAMORPHIC = "crayg/camera/lens/isAnamorphic";
const std::string ImageMetadataTokens::CAMERA_LENS_SQUEEZE = "crayg/camera/lens/squeeze";
const std::string ImageMetadataTokens::CAMERA_LENS_CLOSEST_FOCAL_DISTANCE = "crayg/camera/lens/clostestFocalDistance";
const std::string ImageMetadataTokens::CAMERA_LENS_PATENT = "crayg/camera/lens/patent";
const std::string ImageMetadataTokens::CAMERA_LENS_DESCRIPTION = "crayg/camera/lens/description";
const std::string ImageMetadataTokens::SCENE_STATS_OBJECT_COUNT = "crayg/scene/stats/objectCount";
const std::string ImageMetadataTokens::SCENE_STATS_PRIMITIVE_COUNT = "crayg/scene/stats/primitiveCount";

} // crayg