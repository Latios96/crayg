#define CATCH_CONFIG_RUNNER

#include "Initialization.h"
#include "fixtures/TemporaryDirectory.h"
#include "utils/tracing/CraygTracing.h"
#include <catch2/catch.hpp>
#include <fmt/format.h>

int main(int argc, char *argv[]) {
    crayg::TemporaryDirectory temporaryDirectory;
    crayg::Initialization::initialize();
    CRG_IF_TRACE({
        std::string traceFilePath = temporaryDirectory.getFilePath("trace.json");
        std::cout << fmt::format("Tracing enabled, tracing to {}", traceFilePath) << std::endl;
        mtr_init(traceFilePath.c_str());
    });

    int result = Catch::Session().run(argc, argv);

    CRG_IF_TRACE({
        mtr_flush();
        std::cout << "Shutting down trace." << std::endl;
        mtr_shutdown();
        std::cout << "Flushing trace." << std::endl;
    });
    return result;
}
