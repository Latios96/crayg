#define CATCH_CONFIG_RUNNER

#include "Initialization.h"

#include <catch2/catch.hpp>

int main(int argc, char *argv[]) {
    crayg::Initialization::initialize();

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}
