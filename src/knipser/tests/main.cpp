//
// Created by Jan Honsbrok on 2019-08-10.
//
#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

int main(int argc, char *argv[]) {
    // global setup..

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}



