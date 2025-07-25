#define CATCH_CONFIG_RUNNER

#include "utils/tracing/CraygTracing.h"
#include <catch2/catch.hpp>
#include <fmt/format.h>

int main(int argc, char *argv[]) {
    CRAYG_IF_TRACING_ENABLED({
        std::string traceFilePath = "trace.json";
        std::cout << fmt::format("Tracing enabled, tracing to {}", traceFilePath) << std::endl;
        mtr_init(traceFilePath.c_str());
    });

    int result = Catch::Session().run(argc, argv);

    CRAYG_IF_TRACING_ENABLED({
        mtr_flush();
        std::cout << "Shutting down trace." << std::endl;
        mtr_shutdown();
        std::cout << "Flushing trace." << std::endl;
    });
    return result;
}
