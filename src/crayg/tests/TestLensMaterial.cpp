#include "scene/camera/realistic/LensMaterial.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensMaterial::findMaterialByIorAndAbbe") {
    std::vector<NLensMaterial> testMaterials = {
        {LensMaterialId::SCHOTT_LF5HTI, 1.4, 5, {}},      {LensMaterialId::SCHOTT_LLF1, 1.4, 5.01, {}},
        {LensMaterialId::SCHOTT_LLF1HTI, 1.4, 5.02, {}},  {LensMaterialId::SCHOTT_N_BAF10, 1.41, 5.01, {}},
        {LensMaterialId::SCHOTT_N_BAF4, 1.412, 5.12, {}}, {LensMaterialId::SCHOTT_N_BAF51, 1.5, 5.13, {}},
        {LensMaterialId::SCHOTT_N_BAF52, 1.51, 5.5, {}},
    };

    std::sort(testMaterials.begin(), testMaterials.end(),
              [](const NLensMaterial &a, const NLensMaterial &b) { return a.ior < b.ior; }); // todo extract predicates

    SECTION("should find material with exact ior and abbe no") {
        const auto material = NLensMaterial::findMaterialByIorAndAbbe(1.4, 5, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LF5HTI);
    }

    SECTION("should find material with multiple exact ior and roughly matching abbe no") {
        const auto material = NLensMaterial::findMaterialByIorAndAbbe(1.4, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LLF1);
    }

    SECTION("should find material with roughly matching ior and roughly matching abbe no") {
        const auto material = NLensMaterial::findMaterialByIorAndAbbe(1.4101, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_N_BAF10);
    }

    SECTION("should find material with roughly matching ior if its the last material") {
        const auto material = NLensMaterial::findMaterialByIorAndAbbe(1.515, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_N_BAF52);
    }
    SECTION("should find material with roughly matching ior if its the first material") {
        const auto material = NLensMaterial::findMaterialByIorAndAbbe(1.39, 5, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LF5HTI);
    }

    SECTION("should not find material if ior difference is too large") {
        auto material = NLensMaterial::findMaterialByIorAndAbbe(1.62, 5.015, testMaterials);
        REQUIRE(material == std::nullopt);

        material = NLensMaterial::findMaterialByIorAndAbbe(1.29, 5.015, testMaterials);
        REQUIRE(material == std::nullopt);
    }

    SECTION("should not find material if abbe no difference is too large") {
        auto material = NLensMaterial::findMaterialByIorAndAbbe(1.4, 3.9, testMaterials);
        REQUIRE(material == std::nullopt);

        material = NLensMaterial::findMaterialByIorAndAbbe(1.4, 6.1, testMaterials);
        REQUIRE(material == std::nullopt);
    }
}

}