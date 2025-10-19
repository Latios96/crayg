#include "renderer/integrators/IntegratorSettings.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("IntegratorSettings::getOrDefault") {

    std::unordered_map<std::string, IntegratorSettingsValue> values;
    values["INTEGRATOR_NAME:string_value"] = {"my_value"};
    values["INTEGRATOR_NAME:int_value"] = {1};
    values["INTEGRATOR_NAME:float_value"] = {2.0f};
    IntegratorSettings integratorSettings(values);

    SECTION("should return existing string value") {
        const auto variant = integratorSettings.getOrDefault("INTEGRATOR_NAME:string_value", {"my_default"});
        const auto stringValue = std::get<std::string>(variant);

        REQUIRE(stringValue == "my_value");
    }

    SECTION("should return existing int value") {
        const auto variant = integratorSettings.getOrDefault("INTEGRATOR_NAME:int_value", {42});
        const auto intValue = std::get<int>(variant);

        REQUIRE(intValue == 1);
    }

    SECTION("should return existing float value") {
        const auto variant = integratorSettings.getOrDefault("INTEGRATOR_NAME:float_value", {42.0f});
        const auto intValue = std::get<float>(variant);

        REQUIRE(intValue == 2.0f);
    }

    SECTION("should return default string value") {
        const auto variant = integratorSettings.getOrDefault("NOT_EXISTING", {"my_default"});
        const auto stringValue = std::get<std::string>(variant);

        REQUIRE(stringValue == "my_default");
    }

    SECTION("should return default int value") {
        const auto variant = integratorSettings.getOrDefault("NOT_EXISTING", {42});
        const auto intValue = std::get<int>(variant);

        REQUIRE(intValue == 42);
    }

    SECTION("should return default float value") {
        const auto variant = integratorSettings.getOrDefault("NOT_EXISTING", {42.0f});
        const auto intValue = std::get<float>(variant);

        REQUIRE(intValue == 42.0f);
    }
}

TEST_CASE("IntegratorSettings::==") {

    std::unordered_map<std::string, IntegratorSettingsValue> values;
    values["INTEGRATOR_NAME:string_value"] = {"my_value"};
    IntegratorSettings integratorSettings(values);
    std::unordered_map<std::string, IntegratorSettingsValue> otherValues;
    otherValues["INTEGRATOR_NAME:string_value"] = {"my_other_value"};

    SECTION("sames values should be equal") {
        IntegratorSettings otherIntegratorSettings(values);

        REQUIRE(integratorSettings == otherIntegratorSettings);
    }

    SECTION("different values should not be equal") {
        IntegratorSettings otherIntegratorSettings(otherValues);

        REQUIRE(integratorSettings != otherIntegratorSettings);
    }

    SECTION("different keys should not be equal") {
        IntegratorSettings otherIntegratorSettings;

        REQUIRE(integratorSettings != otherIntegratorSettings);
    }
}

}