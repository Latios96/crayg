#include "Logger.h"
#include "KnipserApp.h"
#include "imageTests.h"
#include "sceneIO.h"

int main(int argc, char **argv) {
    crayg::Logger::initialize();

    knipser::TestRegistry testRegistry;
    testRegistry.registerTests(crayg::sceneIoTests())
        .registerTests(crayg::imageTests());

    KNIPSER_MAIN(testRegistry);
}