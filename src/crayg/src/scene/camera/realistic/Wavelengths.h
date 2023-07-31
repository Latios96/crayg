#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_WAVELENGTHS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_WAVELENGTHS_H_
#include "utils/DtoUtils.h"

namespace crayg {

CRAYG_DTO_3(FraunhoferLine, std::string, symbol, std::string, elementName, float, wavelength);

class FraunhoferLines {
  public:
    static const FraunhoferLine SODIUM;
    static const FraunhoferLine MERCURY;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_REALISTIC_WAVELENGTHS_H_
