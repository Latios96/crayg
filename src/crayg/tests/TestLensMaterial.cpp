#include "scene/camera/realistic/LensMaterial.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("LensMaterial::findMaterialByIorAndAbbe") {
    std::vector<LensMaterial> testMaterials = {
        {LensMaterialId::SCHOTT_LF5HTI, 1.4, 5, {}},      {LensMaterialId::SCHOTT_LLF1, 1.4, 5.01, {}},
        {LensMaterialId::SCHOTT_LLF1HTI, 1.4, 5.02, {}},  {LensMaterialId::SCHOTT_N_BAF10, 1.41, 5.01, {}},
        {LensMaterialId::SCHOTT_N_BAF4, 1.412, 5.12, {}}, {LensMaterialId::SCHOTT_N_BAF51, 1.5, 5.13, {}},
        {LensMaterialId::SCHOTT_N_BAF52, 1.51, 5.5, {}},
    };

    std::sort(testMaterials.begin(), testMaterials.end(), LensMaterial::compareByIor);

    SECTION("should find material with exact ior and abbe no") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.4, 5, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LF5HTI);
    }

    SECTION("should find material with multiple exact ior and roughly matching abbe no") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.4, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LLF1);
    }

    SECTION("should find material with roughly matching ior and roughly matching abbe no") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.4101, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_N_BAF10);
    }

    SECTION("should find material with roughly matching ior if its the last material") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.515, 5.015, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_N_BAF52);
    }
    SECTION("should find material with roughly matching ior if its the first material") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.39, 5, testMaterials);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LF5HTI);
    }

    SECTION("should not find material if ior difference is too large") {
        auto material = LensMaterial::findMaterialByIorAndAbbe(1.62, 5.015, testMaterials);
        REQUIRE(material == std::nullopt);

        material = LensMaterial::findMaterialByIorAndAbbe(1.29, 5.015, testMaterials);
        REQUIRE(material == std::nullopt);
    }

    SECTION("should not find material if abbe no difference is too large") {
        auto material = LensMaterial::findMaterialByIorAndAbbe(1.4, 3.9, testMaterials);
        REQUIRE(material == std::nullopt);

        material = LensMaterial::findMaterialByIorAndAbbe(1.4, 6.1, testMaterials);
        REQUIRE(material == std::nullopt);
    }

    SECTION("should find material in generated code") {
        const auto material = LensMaterial::findMaterialByIorAndAbbe(1.54814, 45.47);

        REQUIRE(material->id == LensMaterialId::SCHOTT_LLF1);
    }
}

TEST_CASE("LensMaterial::getIor") {

    SECTION("should return correct ior for Natrium line from Schott catalog") {
        const auto material = LensMaterial::createMaterialById(LensMaterialId::SCHOTT_BK7G18);

        const float ior = material.getIor(589.29);

        REQUIRE(ior == Catch::Detail::Approx(1.51968f));
    }

    SECTION("should return correct ior for Hg line from Schott catalog") {
        const auto material = LensMaterial::createMaterialById(LensMaterialId::SCHOTT_BK7G18);

        const float ior = material.getIor(546.073);

        REQUIRE(ior == Catch::Detail::Approx(1.52170f));
    }

    SECTION("should return correct ior for Natrium line from Ohara catalog") {
        const auto material = LensMaterial::createMaterialById(LensMaterialId::OHARA_S_FPL51);

        const float ior = material.getIor(589.29);

        REQUIRE(ior == Catch::Detail::Approx(1.496945f));
    }

    SECTION("should return correct ior for Hg line from Ohara catalog") {
        const auto material = LensMaterial::createMaterialById(LensMaterialId::OHARA_S_FPL51);

        const float ior = material.getIor(546.073);

        REQUIRE(ior == Catch::Detail::Approx(1.498455f));
    }
}

}