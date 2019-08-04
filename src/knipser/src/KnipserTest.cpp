//
// Created by jan on 03/08/2019.
//

#include "KnipserTest.h"

#include <utility>

KnipserTest::KnipserTest(std::string name, std::function<void(TestContext)> testCallback)
    : name(std::move(name)), testCallback(std::move(testCallback)) {}

