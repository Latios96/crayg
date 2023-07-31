#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_

#include "utils/EnumUtils.h"
#include <ostream>

namespace crayg {

enum class LensMaterialId {
    UNKNOWN,
    AIR,
#include "materials/LensMaterialIds_ohara.h"
#include "materials/LensMaterialIds_schott.h"
};

struct LensMaterial {
    LensMaterialId id = LensMaterialId::UNKNOWN;
    float ior = 1;
    float abbeNo = 0;
    std::array<float, 6> sellmeierCoefficients = {0, 0, 0, 0, 0, 0};

    LensMaterial() = default;
    LensMaterial(const LensMaterialId &id, float ior, float abbeNo, const std::array<float, 6> &sellmeierCoefficients);

    bool operator==(const LensMaterial &rhs) const;
    bool operator!=(const LensMaterial &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const LensMaterial &material);

    static std::vector<LensMaterial> &getAllMaterials();
    static LensMaterial createMaterialById(LensMaterialId lensMaterialId);
    static std::optional<LensMaterial> findMaterialByIorAndAbbe(float ior, float abbeNo);
    static std::optional<LensMaterial> findMaterialByIorAndAbbe(float ior, float abbeNo,
                                                                const std::vector<LensMaterial> &allMaterials);

    static bool compareByIor(const LensMaterial &a, const LensMaterial &b) {
        return a.ior < b.ior;
    }

    static bool compareByAbbeNo(const LensMaterial &a, const LensMaterial &b) {
        return a.abbeNo < b.abbeNo;
    }

    float getIor(float lambda_nm) const;

  private:
    float sellmeierTerm(float lambdaSquared, int index) const;
};

inline std::ostream &operator<<(std::ostream &os, const crayg::LensMaterialId &v) {
    os << fmt::format("{}", v);
    return os;
}
}

template <> struct fmt::formatter<crayg::LensMaterial> : ostream_formatter {};

CRAYG_FMT_ENUM_FORMATTER(crayg::LensMaterialId);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_
