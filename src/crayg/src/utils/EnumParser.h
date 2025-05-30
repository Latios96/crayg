#pragma once

#include "utils/Exceptions.h"
#include <fmt/format.h>
#include <magic_enum.hpp>
#include <string>

namespace crayg {

class EnumParser {
  public:
    template <typename T> static std::optional<T> parse(const std::string &string) {
        std::string upper = string;
        for (auto &c : upper) {
            c = toupper(c);
        }
        return magic_enum::enum_cast<T>(upper);
    }

    template <typename T> static std::optional<T> parse(int value) {
        return magic_enum::enum_cast<T>(value);
    }

    template <typename T> static T parseOrThrow(const std::string &string) {
        auto maybeValue = EnumParser::parse<T>(string);
        if (!maybeValue.has_value()) {
            CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format(R"(Unsupported enum value '{}')", string)));
        }
        return maybeValue.value();
    }

    template <typename T> static T parseOrThrow(int value) {
        auto maybeValue = EnumParser::parse<T>(value);
        if (!maybeValue.has_value()) {
            CRAYG_LOG_AND_THROW(std::runtime_error(fmt::format(R"(Unsupported enum value '{}')", value)));
        }
        return maybeValue.value();
    }

    template <typename T> static T parseOrDefault(const std::string &string, T defaultValue) {
        auto maybeValue = EnumParser::parse<T>(string);
        return maybeValue.value_or(defaultValue);
    }

    template <typename T> static T parseOrDefault(int value, T defaultValue) {
        auto maybeValue = EnumParser::parse<T>(value);
        return maybeValue.value_or(defaultValue);
    }
};
}
