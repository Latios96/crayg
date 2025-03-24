#pragma once

#include <fmt/ostream.h>
#include <ostream>

namespace crayg {

struct Resolution {
  public:
    Resolution() = default;
    Resolution(int width, int height);
    Resolution(const Resolution &resolution);
    static Resolution parse(const std::string &resolutionString);

    template <typename T> static Resolution deduce(const T &t) {
        return Resolution(t.getWidth(), t.getHeight());
    }

    bool operator==(const Resolution &rhs) const;
    bool operator!=(const Resolution &rhs) const;
    bool operator<(const Resolution &rhs) const;
    bool operator>(const Resolution &rhs) const;
    bool operator<=(const Resolution &rhs) const;
    bool operator>=(const Resolution &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Resolution &resolution);
    int getWidth() const;
    int getHeight() const;

    float getRatio() const;

  private:
    int width, height;
};

}

template <> struct fmt::formatter<crayg::Resolution> : ostream_formatter {};
