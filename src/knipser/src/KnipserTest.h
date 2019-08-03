//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_KNIPSERTEST_H_
#define CRAYG_SRC_KNIPSER_SRC_KNIPSERTEST_H_

#include <string>
#include <functional>
#include "TestContext.h"

class KnipserTest {
 public:
    KnipserTest(const std::string &name, const std::function<void(TestContext)> &testCallback);
    const std::string &getName() const;
    const std::function<void(TestContext)> &getTestCallback() const;
 private:
    std::string name;
    std::function<void(TestContext)> testCallback;
};

#endif //CRAYG_SRC_KNIPSER_SRC_KNIPSERTEST_H_
