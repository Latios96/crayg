#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_

#include <ostream>

namespace crayg {

struct Resolution {
  public:
    Resolution();
    Resolution(int width, int height);
    Resolution(const Resolution &resolution);
    static Resolution parse(const std::string &resolutionString);
    bool operator==(const Resolution &rhs) const;
    bool operator!=(const Resolution &rhs) const;
    bool operator<(const Resolution &rhs) const;
    bool operator>(const Resolution &rhs) const;
    bool operator<=(const Resolution &rhs) const;
    bool operator>=(const Resolution &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);
    int getWidth() const;
    int getHeight() const;

  private:
    int width, height;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_BASICS_RESOLUTION_H_
