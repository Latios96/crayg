//
// Created by jan on 03/08/2019.
//

#include "KnipserTest.h"
KnipserTest::KnipserTest(const std::string &name, const std::function<void(TestContext)> &testCallback)
    : name(name), testCallback(testCallback) {}
const std::string &KnipserTest::getName() const {
    return name;
}
const std::function<void(TestContext)> &KnipserTest::getTestCallback() const {
    return testCallback;
}
