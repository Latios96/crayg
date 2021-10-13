//
// Created by Jan on 24.11.2020.
//
#include <catch2/catch.hpp>
#include <utils/ReadableFormatter.h>

TEST_CASE("ReadableFormatter should format time", "[TestReadableFormatter]") {

    ReadableFormatter readableFormatter;

    SECTION("less than one second") {
        std::string result =
            readableFormatter.formatDuration(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(
                1)));
        REQUIRE(result == "less than one second");
    }

    SECTION("one second") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(1));
        REQUIRE(result == "1 second");
    }

    SECTION("seconds only") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(10));
        REQUIRE(result == "10 seconds");
    }

    SECTION("one minute") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(60));
        REQUIRE(result == "1 minute");
    }

    SECTION("minute and second") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(61));
        REQUIRE(result == "1 minute 1 second");
    }

    SECTION("minute and seconds") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(62));
        REQUIRE(result == "1 minute 2 seconds");
    }

    SECTION("minutes and seconds") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(122));
        REQUIRE(result == "2 minutes 2 seconds");
    }

    SECTION("hour") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(3600));
        REQUIRE(result == "1 hour");
    }

    SECTION("hour and second") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(3601));
        REQUIRE(result == "1 hour 1 second");
    }

    SECTION("hour and seconds") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(3602));
        REQUIRE(result == "1 hour 2 seconds");
    }

    SECTION("hour and minute") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(3660));
        REQUIRE(result == "1 hour 1 minute");
    }

    SECTION("hour and minute and second") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(3661));
        REQUIRE(result == "1 hour 1 minute 1 second");
    }

    SECTION("long time") {
        std::string result = readableFormatter.formatDuration(std::chrono::seconds(64581));
        REQUIRE(result == "17 hours 56 minutes 21 seconds");
    }

}