#include "sceneIO/usd/UsdUtils.h"
#include <catch2/catch.hpp>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/sphere.h>

namespace crayg {

enum class UsdUtilsTestEnum { MY_FIRST_VALUE = 1, MY_SECOND_VALUE = 2 };

template <> struct UsdTypeUtil<UsdUtilsTestEnum> {
    inline static pxr::SdfValueTypeName sdfValueTypeName = pxr::SdfValueTypeNames->Token;

    static pxr::TfToken convert(UsdUtilsTestEnum testEnum) {
        return pxr::TfToken(fmt::format("{}", magic_enum::enum_name(testEnum)));
    }
};

TEST_CASE("UsdUtils::getAttributeValueAs") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto sphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/sphere"));
    sphere.GetRadiusAttr().Set(3.0);

    SECTION("should read attribute value") {
        auto radius = UsdUtils::getStaticAttributeValueAs<double>(sphere.GetRadiusAttr());

        REQUIRE(radius == 3.0);
    }

    SECTION("should throw exception when there is an error reading the attribute") {
        REQUIRE_THROWS_AS(UsdUtils::getStaticAttributeValueAs<float>(sphere.GetRadiusAttr()), std::runtime_error);
    }
}

TEST_CASE("UsdUtils::readEnumValue") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto sphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/sphere"));
    sphere.GetRadiusAttr().Set(3.0);

    SECTION("should read authored enum value") {
        sphere.GetPrim()
            .CreateAttribute(pxr::TfToken("myEnumAttribute"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("MY_FIRST_VALUE"));

        auto myEnumValue =
            UsdUtils::readEnumValue(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_SECOND_VALUE);

        REQUIRE(myEnumValue == UsdUtilsTestEnum::MY_FIRST_VALUE);
    }

    SECTION("should read authored enum value case insensitive") {
        sphere.GetPrim()
            .CreateAttribute(pxr::TfToken("myEnumAttribute"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("My_FiRST_Value"));

        auto myEnumValue =
            UsdUtils::readEnumValue(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_SECOND_VALUE);

        REQUIRE(myEnumValue == UsdUtilsTestEnum::MY_FIRST_VALUE);
    }

    SECTION("reading not authored enum value should fallback to default") {
        auto myEnumValue =
            UsdUtils::readEnumValue(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_SECOND_VALUE);

        REQUIRE(myEnumValue == UsdUtilsTestEnum::MY_SECOND_VALUE);
    }

    SECTION("should throw when reading invalud enum value") {
        sphere.GetPrim()
            .CreateAttribute(pxr::TfToken("myEnumAttribute"), pxr::SdfValueTypeNames->Token)
            .Set(pxr::TfToken("invalid"));

        REQUIRE_THROWS_AS(
            UsdUtils::readEnumValue(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_SECOND_VALUE),
            std::runtime_error);
    }
}

TEST_CASE("UsdUtils::createAndSetAttribute") {

    auto stage = pxr::UsdStage::CreateInMemory();
    auto sphere = pxr::UsdGeomSphere::Define(stage, pxr::SdfPath("/sphere"));
    sphere.GetRadiusAttr().Set(3.0);

    SECTION("should create and set int attribute") {
        UsdUtils::createAndSetAttribute(sphere.GetPrim(), "myIntAttribute", 5);

        auto value =
            UsdUtils::getStaticAttributeValueAs<int>(sphere.GetPrim().GetAttribute(pxr::TfToken("myIntAttribute")));

        REQUIRE(value == 5);
    }

    SECTION("should create and set float attribute") {
        UsdUtils::createAndSetAttribute(sphere.GetPrim(), "myFloatAttribute", 5.f);

        auto value =
            UsdUtils::getStaticAttributeValueAs<float>(sphere.GetPrim().GetAttribute(pxr::TfToken("myFloatAttribute")));

        REQUIRE(value == 5.f);
    }

    SECTION("should create and set string attribute") {
        UsdUtils::createAndSetAttribute(sphere.GetPrim(), "myStringAttribute", std::string("my string"));

        auto value = UsdUtils::getStaticAttributeValueAs<std::string>(
            sphere.GetPrim().GetAttribute(pxr::TfToken("myStringAttribute")));

        REQUIRE(value == "my string");
    }

    SECTION("should create and set enum attribute") {
        UsdUtils::createAndSetAttribute(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_FIRST_VALUE);

        auto value = UsdUtils::readEnumValue(sphere.GetPrim(), "myEnumAttribute", UsdUtilsTestEnum::MY_FIRST_VALUE);

        REQUIRE(value == UsdUtilsTestEnum::MY_FIRST_VALUE);
    }
}

}