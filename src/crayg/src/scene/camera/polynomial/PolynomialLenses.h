#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALLENSES_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALLENSES_H_

#include "utils/EnumUtils.h"

namespace crayg {

enum PolynomialLens { BICONVEX, ANGENIEUX_DOUBLE_GAUSS, CANON_70MM };

inline float getFocalLength(PolynomialLens polynomialLens) {
    switch (polynomialLens) {
    case BICONVEX:
        return 49.8;
    case ANGENIEUX_DOUBLE_GAUSS:
        return 50;
    case CANON_70MM:
        return 72;
    }
}

inline float getOuterPupilRadius(PolynomialLens polynomialLens) {
    switch (polynomialLens) {
    case BICONVEX:
        return 12.700000;
    case ANGENIEUX_DOUBLE_GAUSS:
        return 27.000000;
    case CANON_70MM:
        return 38.000000;
    }
}

inline float getInnerPupilRadius(PolynomialLens polynomialLens) {
    switch (polynomialLens) {
    case BICONVEX:
        return 12.700000;
    case ANGENIEUX_DOUBLE_GAUSS:
        return 13.500000;
    case CANON_70MM:
        return 21.000000;
    }
}

inline float getOuterPupilCurvatureRadius(PolynomialLens polynomialLens) {
    switch (polynomialLens) {
    case BICONVEX:
        return 10000;
    case ANGENIEUX_DOUBLE_GAUSS:
        return 82.099998;
    case CANON_70MM:
        return 311.919006;
    }
}

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PolynomialLens);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_POLYNOMIAL_POLYNOMIALLENSES_H_
