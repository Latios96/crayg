//
// Created by Jan Honsbrok on 2019-08-11.
//

#include <fmt/format.h>
#include "BasicAssertion.h"

BasicAssertion::BasicAssertion(const std::string &file, const int lineNumber) : file(file), lineNumber(lineNumber) {}

std::string BasicAssertion::createMessage(const std::string &assertionMessage) const {
    return fmt::format("{}:{}: Failure:\n{}", file, lineNumber, assertionMessage);
}
