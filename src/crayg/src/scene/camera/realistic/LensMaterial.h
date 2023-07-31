#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_

#include "utils/EnumUtils.h"
#include <ostream>

namespace crayg {

// Materials taken from Schott Glas Catalog, 2022, Ohara Catalog 2023

enum LensMaterial {
    UNKNOWN,
    BK7G18,
    F2,
    F2G12,
    F2HT,
    F2HTi,
    F5,
    FK5HTi,
    K10,
    K5G20,
    K7,
    LAFN7,
    LAK9G15,
    LASF35,
    LF5,
    LF5G19,
    LF5HTi,
    LLF1,
    LLF1HTi,
    N_BAF10,
    N_BAF4,
    N_BAF51,
    N_BAF52,
    N_BAK1,
    N_BAK2,
    N_BAK4,
    N_BAK4HT,
    N_BALF4,
    N_BALF5,
    N_BASF2,
    N_BASF64,
    N_BK10,
    N_BK7,
    N_BK7HT,
    N_BK7HTi,
    N_F2,
    N_FK5,
    N_FK51A,
    N_FK58,
    N_K5,
    N_KF9,
    N_KZFS11,
    N_KZFS2,
    N_KZFS4,
    N_KZFS4HT,
    N_KZFS5,
    N_KZFS8,
    N_LAF2,
    N_LAF21,
    N_LAF33,
    N_LAF34,
    N_LAF35,
    N_LAF7,
    N_LAK10,
    N_LAK12,
    N_LAK14,
    N_LAK21,
    N_LAK22,
    N_LAK28,
    N_LAK33B,
    N_LAK34,
    N_LAK7,
    N_LAK8,
    N_LAK9,
    N_LASF31A,
    N_LASF40,
    N_LASF41,
    N_LASF43,
    N_LASF44,
    N_LASF45,
    N_LASF45HT,
    N_LASF46A,
    N_LASF46B,
    N_LASF55,
    N_LASF9,
    N_LASF9HT,
    N_PK51,
    N_PK52A,
    N_PSK3,
    N_PSK53A,
    N_SF1,
    N_SF10,
    N_SF11,
    N_SF14,
    N_SF15,
    N_SF2,
    N_SF4,
    N_SF5,
    N_SF57,
    N_SF57HT,
    N_SF57HTultra,
    N_SF6,
    N_SF66,
    N_SF6HT,
    N_SF6HTultra,
    N_SF6Q2,
    N_SF8,
    N_SK11,
    N_SK14,
    N_SK16,
    N_SK2,
    N_SK2HT,
    N_SK4,
    N_SK5,
    N_SK5HTi,
    N_SSK2,
    N_SSK5,
    N_SSK8,
    N_ZK7,
    N_ZK7A,
    P_BK7,
    P_LAF37,
    P_LAK35,
    P_LASF47,
    P_LASF50,
    P_LASF51,
    P_SF68,
    P_SF69,
    P_SF8,
    P_SK57,
    P_SK57Q1,
    P_SK58A,
    P_SK60,
    SF1,
    SF10,
    SF11,
    SF2,
    SF3,
    SF4,
    SF5,
    SF56A,
    SF57,
    SF57HTultra,
    SF6,
    SF6G05,
    SF6HT,
};

enum class LensMaterialId {
    UNKNOWN,
#include "materials/LensMaterialIds_ohara.h"
#include "materials/LensMaterialIds_schott.h"
};

struct NLensMaterial {
    LensMaterialId id = LensMaterialId::UNKNOWN;
    float ior = 1;
    float abbeNo = 0;
    std::array<float, 6> sellmeierCoefficients = {0, 0, 0, 0, 0, 0};

    NLensMaterial() = default;
    NLensMaterial(const LensMaterialId &id, float ior, float abbeNo, const std::array<float, 6> &sellmeierCoefficients);

    bool operator==(const NLensMaterial &rhs) const;
    bool operator!=(const NLensMaterial &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const NLensMaterial &material);

    static std::vector<NLensMaterial> &getAllMaterials();
    static NLensMaterial createMaterialById(LensMaterialId lensMaterialId);
    static std::optional<NLensMaterial> findMaterialByIorAndAbbe(float ior, float abbeNo);
    static std::optional<NLensMaterial> findMaterialByIorAndAbbe(float ior, float abbeNo,
                                                                 const std::vector<NLensMaterial> &allMaterials);

    static bool compareByIor(const NLensMaterial &a, const NLensMaterial &b) {
        return a.ior < b.ior;
    }

    static bool compareByAbbeNo(const NLensMaterial &a, const NLensMaterial &b) {
        return a.abbeNo < b.abbeNo;
    }
};

inline std::ostream &operator<<(std::ostream &os, const crayg::LensMaterialId &v) {
    os << fmt::format("{}", v);
    return os;
}
}

template <> struct fmt::formatter<crayg::NLensMaterial> : ostream_formatter {};

CRAYG_FMT_ENUM_FORMATTER(crayg::LensMaterial);
CRAYG_FMT_ENUM_FORMATTER(crayg::LensMaterialId);

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_CAMERA_LENSMATERIAL_H_
