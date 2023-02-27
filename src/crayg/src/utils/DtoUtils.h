#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_DTOUTILS_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_DTOUTILS_H_

#include "ToStringHelper.h"
#include <fmt/ostream.h>
#include <ostream>
#include <string>
#include <vector>

#define CRAYG_DTO_UTILS_VECTOR_FORMATTER(Name)                                                                         \
    template <> struct fmt::formatter<std::vector<crayg::Name>> {                                                      \
        template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }               \
                                                                                                                       \
        template <typename FormatContext> auto format(std::vector<crayg::Name> const &dtos, FormatContext &ctx) {      \
            return fmt::format_to(ctx.out(), "[{}]", fmt::join(dtos, ", "));                                           \
        };                                                                                                             \
    };

#define CRAYG_DTO_2(Name, FirstType, FirstName, SecondType, SecondName)                                                \
    struct Name {                                                                                                      \
        FirstType FirstName = FirstType();                                                                             \
        SecondType SecondName = SecondType();                                                                          \
                                                                                                                       \
        Name() = default;                                                                                              \
                                                                                                                       \
        Name(FirstType FirstName, SecondType SecondName) : FirstName(FirstName), SecondName(SecondName) {}             \
                                                                                                                       \
        Name(const Name &name) : FirstName(name.FirstName), SecondName(name.SecondName) {}                             \
                                                                                                                       \
        bool operator==(const Name &rhs) const { return FirstName == rhs.FirstName && SecondName == rhs.SecondName; }  \
        bool operator!=(const Name &rhs) const { return !(rhs == *this); }                                             \
        friend std::ostream &operator<<(std::ostream &os, const Name &dto) {                                           \
            os << fmt::format("{}", dto);                                                                              \
            return os;                                                                                                 \
        }                                                                                                              \
    };                                                                                                                 \
    } /*namespace*/                                                                                                    \
    template <> struct fmt::formatter<crayg::Name> {                                                                   \
        template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }               \
                                                                                                                       \
        template <typename FormatContext> auto format(crayg::Name const &dto, FormatContext &ctx) {                    \
            return fmt::format_to(ctx.out(), "{}{{{}={},{}={}}}", #Name, #FirstName, dto.FirstName, #SecondName,       \
                                  dto.SecondName);                                                                     \
        };                                                                                                             \
    };                                                                                                                 \
    CRAYG_DTO_UTILS_VECTOR_FORMATTER(Name)                                                                             \
    namespace crayg {

#define CRAYG_DTO_3(Name, FirstType, FirstName, SecondType, SecondName, ThirdType, ThirdName)                          \
    struct Name {                                                                                                      \
        FirstType FirstName = FirstType();                                                                             \
        SecondType SecondName = SecondType();                                                                          \
        ThirdType ThirdName = ThirdType();                                                                             \
                                                                                                                       \
        Name() = default;                                                                                              \
                                                                                                                       \
        Name(FirstType FirstName, SecondType SecondName, ThirdType ThirdName)                                          \
            : FirstName(FirstName), SecondName(SecondName), ThirdName(ThirdName) {}                                    \
                                                                                                                       \
        Name(const Name &name) : FirstName(name.FirstName), SecondName(name.SecondName), ThirdName(name.ThirdName) {}  \
                                                                                                                       \
        bool operator==(const Name &rhs) const {                                                                       \
            return FirstName == rhs.FirstName && SecondName == rhs.SecondName && ThirdName == rhs.ThirdName;           \
        }                                                                                                              \
        bool operator!=(const Name &rhs) const { return !(rhs == *this); }                                             \
        friend std::ostream &operator<<(std::ostream &os, const Name &dto) {                                           \
            os << fmt::format("{}", dto);                                                                              \
            return os;                                                                                                 \
        }                                                                                                              \
    };                                                                                                                 \
    } /*namespace*/                                                                                                    \
    template <> struct fmt::formatter<crayg::Name> {                                                                   \
        template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }               \
                                                                                                                       \
        template <typename FormatContext> auto format(crayg::Name const &dto, FormatContext &ctx) {                    \
            return fmt::format_to(ctx.out(), "{}{{{}={},{}={},{}={}}}", #Name, #FirstName, dto.FirstName, #SecondName, \
                                  dto.SecondName, #ThirdName, dto.ThirdName);                                          \
        };                                                                                                             \
    };                                                                                                                 \
    CRAYG_DTO_UTILS_VECTOR_FORMATTER(Name)                                                                             \
    namespace crayg {

#endif // CRAYG_SRC_CRAYG_SRC_UTILS_DTOUTILS_H_
