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
    KnipserTest(std::string name, std::function<void(TestContext&)> testCallback);

    const std::string name;
    const std::function<void(TestContext&)> testCallback;

    bool operator==(const KnipserTest &rhs) const;

    bool operator!=(const KnipserTest &rhs) const;
};

#endif //CRAYG_SRC_KNIPSER_SRC_KNIPSERTEST_H_
