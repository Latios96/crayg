#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_PAIRDTO_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_PAIRDTO_H_

#include <string>
#include <ostream>
#include "ToStringHelper.h"

#define CRAYG_PAIR_DTO(Name, FirstType, FirstName, SecondType, SecondName) \
struct Name {\
    FirstType FirstName = FirstType();                                                   \
    SecondType SecondName = SecondType();                                                 \
                                                                           \
    Name() = default;                                                      \
                                                                           \
    Name(FirstType FirstName,SecondType SecondName):FirstName(FirstName),SecondName(SecondName){} \
                                                                           \
    Name(const Name &name):FirstName(name.FirstName),SecondName(name.SecondName){} \
                                                                           \
    bool operator==(const Name &rhs) const { \
        return FirstName == rhs.FirstName && \
            SecondName == rhs.SecondName; \
    } \
    bool operator!=(const Name &rhs) const { \
        return !(rhs == *this); \
    } \
    friend std::ostream &operator<<(std::ostream &os, const Name &dto) { \
        os << ToStringHelper(#Name) \
            .addMember(#FirstName, dto.FirstName) \
            .addMember(#SecondName, dto.SecondName) \
            .finish(); \
        return os; \
    }\
};\

#endif //CRAYG_SRC_CRAYG_SRC_UTILS_PAIRDTO_H_
