//
// Created by jan on 03/08/2019.
//
#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

int main(int argc, char *argv[]) {
  // global setup..

  int result = Catch::Session().run(argc, argv);

  // global clean-up...

  return result;
}


