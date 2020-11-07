#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>
#include <basics/Vector3f.h>

int main() {
    ankerl::nanobench::Bench().minEpochIterations(10000).run("Vector3f add", [&] {
        Vector3f d = Vector3f(0, 0, 0) + Vector3f(1, 2, 3);
        ankerl::nanobench::doNotOptimizeAway(d);
    });
    ankerl::nanobench::Bench().minEpochIterations(10000).run("Vector3 add", [&] {
        Vector3f d = Vector3f(0, 0, 0) + Vector3f(1, 2, 3);
        ankerl::nanobench::doNotOptimizeAway(d);
    });
}