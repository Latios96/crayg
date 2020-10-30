//
// Created by Jan on 30.10.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_

#include <ostream>
struct Resolution {
 public:
    const int width, height;
    Resolution();
    Resolution(int width, int height);
    bool operator==(const Resolution &rhs) const;
    bool operator!=(const Resolution &rhs) const;
    bool operator<(const Resolution &rhs) const;
    bool operator>(const Resolution &rhs) const;
    bool operator<=(const Resolution &rhs) const;
    bool operator>=(const Resolution &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);
};

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_
