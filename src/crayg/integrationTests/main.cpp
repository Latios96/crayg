//
// Created by Jan Honsbrok on 01.10.19.
//
#include "Logger.h"
#include "KnipserApp.h"
#include "imageTests.h"
#include "renderTests.h"
#include "sceneIO.h"

int main(int argc, char **argv) {
    Logger::initialize();

    TestRegistry testRegistry;
    testRegistry
        .registerTests(sceneIoTests())
        .registerTests(imageTests())
        .registerTests(renderTests());

    KNIPSER_MAIN(testRegistry);
}