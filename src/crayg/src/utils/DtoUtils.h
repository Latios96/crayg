#pragma once

#include <fmt/ostream.h>
#include <ostream>
#include <string>
#include <vector>

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
            os << fmt::format("{}{{{}={},{}={}}}", #Name, #FirstName, dto.FirstName, #SecondName, dto.SecondName);     \
            return os;                                                                                                 \
        }                                                                                                              \
    };                                                                                                                 \
    } /*namespace*/                                                                                                    \
    template <> struct fmt::formatter<crayg::Name> : ostream_formatter {};                                             \
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
            os << fmt::format("{}{{{}={},{}={},{}={}}}", #Name, #FirstName, dto.FirstName, #SecondName,                \
                              dto.SecondName, #ThirdName, dto.ThirdName);                                              \
            return os;                                                                                                 \
        }                                                                                                              \
    };                                                                                                                 \
    } /*namespace*/                                                                                                    \
    template <> struct fmt::formatter<crayg::Name> : ostream_formatter {};                                             \
    namespace crayg {
