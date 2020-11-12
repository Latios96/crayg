//
// Created by Jan on 12.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_BASICS_LOMBOKTEST_H_
#define CRAYG_SRC_CRAYG_SRC_BASICS_LOMBOKTEST_H_

#include <string>
#include <ostream>


class LombokBaryCentricLombokTest {
    float alpha, beta, gamma;
    std::string name;
};

class BaryCentricLombokGenImpl {
 public:
    BaryCentricLombokGenImpl() = default;
    BaryCentricLombokGenImpl(float alpha, float beta, float gamma, const std::string &name);

    float getAlpha() const {
        return alpha;
    }
    float getBeta() const {
        return beta;
    }
    float getGamma() const {
        return gamma;
    }
    const std::string &getName() const {
        return name;
    }

    bool operator==(const BaryCentricLombokGenImpl &rhs) const {
        return
            alpha == rhs.alpha &&
            beta == rhs.beta &&
            gamma == rhs.gamma &&
            name == rhs.name
            ;
    }
    bool operator!=(const BaryCentricLombokGenImpl &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const BaryCentricLombokGenImpl &rhs) const {
        if (alpha < rhs.alpha)
            return true;
        if (rhs.alpha < alpha)
            return false;
        if (beta < rhs.beta)
            return true;
        if (rhs.beta < beta)
            return false;
        if (gamma < rhs.gamma)
            return true;
        if (rhs.gamma < gamma)
            return false;
        return name < rhs.name;
    }
    bool operator>(const BaryCentricLombokGenImpl &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const BaryCentricLombokGenImpl &rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const BaryCentricLombokGenImpl &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const BaryCentricLombokGenImpl &lombok) {
        os << "alpha: " << lombok.alpha << " beta: " << lombok.beta << " gamma: " << lombok.gamma << " name: "
           << lombok.name;
        return os;
    }

 private:
    float alpha = 0, beta = 0, gamma = 0;
    std::string name;
};
BaryCentricLombokGenImpl::BaryCentricLombokGenImpl(float alpha, float beta, float gamma, const std::string &name)
    : alpha(alpha), beta(beta), gamma(gamma), name(name) {}

#endif //CRAYG_SRC_CRAYG_SRC_BASICS_LOMBOKTEST_H_
