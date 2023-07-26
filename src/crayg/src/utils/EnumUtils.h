#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_ENUMUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_ENUMUTILS_H_

#include <boost/algorithm/string/case_conv.hpp>
#include <fmt/format.h>
#include <magic_enum.hpp>
#include <string>

#define CRAYG_FMT_ENUM_FORMATTER(FullQualifiedType)                                                                    \
    template <> struct fmt::formatter<FullQualifiedType> {                                                             \
        template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }               \
                                                                                                                       \
        template <typename FormatContext> auto format(FullQualifiedType const &integratorType, FormatContext &ctx) {   \
            return fmt::format_to(ctx.out(), magic_enum::enum_name(integratorType));                                   \
        };                                                                                                             \
    }

namespace crayg {

class EnumUtils {
  public:
    template <typename T> static std::optional<T> parse(const std::string &string) {
        return magic_enum::enum_cast<T>(boost::algorithm::to_upper_copy(string));
    }

    template <typename T> static std::optional<T> parse(int value) {
        return magic_enum::enum_cast<T>(value);
    }

    template <typename T> static T parseOrThrow(const std::string &string) {
        auto maybeValue = EnumUtils::parse<T>(string);
        if (!maybeValue.has_value()) {
            throw std::runtime_error(fmt::format(R"(Unsupported enum value '{}')", string));
        }
        return maybeValue.value();
    }

    template <typename T> static T parseOrThrow(int value) {
        auto maybeValue = EnumUtils::parse<T>(value);
        if (!maybeValue.has_value()) {
            throw std::runtime_error(fmt::format(R"(Unsupported enum value '{}')", value));
        }
        return maybeValue.value();
    }

    template <typename T> static T parseOrDefault(const std::string &string, T defaultValue) {
        auto maybeValue = EnumUtils::parse<T>(string);
        return maybeValue.value_or(defaultValue);
    }

    template <typename T> static T parseOrDefault(int value, T defaultValue) {
        auto maybeValue = EnumUtils::parse<T>(value);
        return maybeValue.value_or(defaultValue);
    }
};
}

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_ENUMUTILS_H_
