//
// Created by Jan Honsbrok on 2019-08-11.
//

#ifndef CRAYG_KNIPSERASSERTIONS_H
#define CRAYG_KNIPSERASSERTIONS_H

#include <string>

class KnipserException : public std::exception {
    const char *what() const throw() {
        return "basic KnipserException";
    }
};

class BasicAssertion {
public:
    BasicAssertion(const std::string &file, const int lineNumber);

    std::string createMessage(const std::string &assertionMessage) const;

protected:
    const std::string file;
    const int lineNumber;
};


#endif //CRAYG_KNIPSERASSERTIONS_H
