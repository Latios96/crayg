//
// Created by jan on 03/08/2019.
//

#include "KnipserTest.h"

#include <utility>

KnipserTest::KnipserTest(std::string name, std::function<void(TestContext)> testCallback)
    : name(std::move(name)), testCallback(std::move(testCallback)) {}

bool KnipserTest::operator==(const KnipserTest &rhs) const {
    return name == rhs.name;
}

bool KnipserTest::operator!=(const KnipserTest &rhs) const {
    return !(rhs == *this);
}

