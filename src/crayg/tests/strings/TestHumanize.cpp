#include "crayg/foundation/strings/Humanize.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("Humanize::naturalFileSize") {

    SECTION("should format correctly") {
        const auto testData = GENERATE(table<size_t, std::string>({{0, "0 Bytes"},        {1, "1 Byte"},
                                                                   {2, "2 Bytes"},        {3, "3 Bytes"},
                                                                   {500, "500 Bytes"},    {1e3 - 1, "999 Bytes"},
                                                                   {1e3, "1.0 kB"},       {1e3 + 1, "1.0 kB"},
                                                                   {1.5 * 1e3, "1.5 kB"}, {1000000 - 1, "1000.0 kB"},
                                                                   {1000000, "1.0 MB"},   {1e6 + 1, "1.0 MB"},
                                                                   {1.5 * 1e6, "1.5 MB"}, {1e9 - 1, "1000.0 MB"},
                                                                   {1e9, "1.0 GB"},       {1e9 + 1, "1.0 GB"},
                                                                   {1.5 * 1e9, "1.5 GB"}, {1e12 - 1, "1000.0 GB"},
                                                                   {1e12, "1.0 TB"},      {1e12 + 1, "1.0 TB"},
                                                                   {1.5 * 1e12, "1.5 TB"}}));

        const size_t bytes = std::get<0>(testData);
        const std::string formatted = std::get<1>(testData);

        REQUIRE(Humanize::naturalFileSize(bytes) == formatted);
    }
}

TEST_CASE("Humanize::naturalDuration") {

    SECTION("less than one second") {
        std::string result =
            Humanize::naturalDuration(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(1)));
        REQUIRE(result == "less than one second");
    }

    SECTION("one second") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(1));
        REQUIRE(result == "1 second");
    }

    SECTION("seconds only") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(10));
        REQUIRE(result == "10 seconds");
    }

    SECTION("one minute") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(60));
        REQUIRE(result == "1 minute");
    }

    SECTION("minute and second") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(61));
        REQUIRE(result == "1 minute 1 second");
    }

    SECTION("minute and seconds") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(62));
        REQUIRE(result == "1 minute 2 seconds");
    }

    SECTION("minutes and seconds") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(122));
        REQUIRE(result == "2 minutes 2 seconds");
    }

    SECTION("hour") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(3600));
        REQUIRE(result == "1 hour");
    }

    SECTION("hour and second") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(3601));
        REQUIRE(result == "1 hour 1 second");
    }

    SECTION("hour and seconds") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(3602));
        REQUIRE(result == "1 hour 2 seconds");
    }

    SECTION("hour and minute") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(3660));
        REQUIRE(result == "1 hour 1 minute");
    }

    SECTION("hour and minute and second") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(3661));
        REQUIRE(result == "1 hour 1 minute 1 second");
    }

    SECTION("long time") {
        std::string result = Humanize::naturalDuration(std::chrono::seconds(64581));
        REQUIRE(result == "17 hours 56 minutes 21 seconds");
    }
}

}
