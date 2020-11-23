//
// Created by Jan Honsbrok on 01.10.19.
//
#include "Logger.h"
#include "KnipserApp.h"
#include "imageTests.h"
#include "renderTests.h"
#include "sceneIO.h"

int main(int argc, char **argv) {
    crayg::Logger::initialize();

    knipser::TestRegistry testRegistry;
    testRegistry
        .registerTests(crayg::sceneIoTests())
        .registerTests(crayg::imageTests())
        .registerTests(crayg::renderTests());

    KNIPSER_MAIN(testRegistry);
}