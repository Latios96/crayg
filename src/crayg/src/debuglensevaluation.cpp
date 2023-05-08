#include "scene/camera/polynomal/lens.h"
#include <array>
#include <fmt/ostream.h>
#include <iostream>

int main() {
    int samples = 0;
    float sum = 0;
    for (float lambda = 0.4; lambda <= 0.7; lambda += 0.01) {
        std::array<float, 5> in = {0, 0, 0, 0, lambda};
        std::array<float, 5> out = {0};
        double transmittance = lens_evaluate(in.data(), out.data());
        samples++;
        sum += transmittance;
        fmt::print("{:.3f} {:.3f}\n", lambda, transmittance);
        std::array<float, 3> cs_origin = {0};
        std::array<float, 3> cs_direction = {0};
        lens_sphereToCs(out.data(), out.data() + 2, cs_origin.data(), cs_direction.data(),
                        -lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
        fmt::print("in {}\nout {}\n", fmt::join(in, ","), fmt::join(out, ","));
    }
    fmt::print("{:.3}", sum / samples);
}