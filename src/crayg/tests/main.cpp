#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include "stacktrace_registration.h"

int main(int argc, char *argv[]) {
    register_signal_handlers();
    std::cout << signal_handler_registration_report() << std::endl;
    int result = Catch::Session().run(argc, argv);
    return result;
}

