#ifndef CRAYG_TOSTRINGHELPER_H
#define CRAYG_TOSTRINGHELPER_H

#include <string>
#include <fmt/format.h>
#include <fmt/ostream.h>

namespace crayg {

class ToStringHelper {
 public:
    explicit ToStringHelper(const std::string &className) {
        repr.append(className);
    }

    template<typename T>
    ToStringHelper &addMember(const std::string &name, T value) {
        if (!hasMembers) {
            repr.append("{");
            hasMembers = true;
            repr.append(name)
                .append("=")
                .append(fmt::format("{}", value));
        } else {
            repr.append(",")
                .append(name)
                .append("=")
                .append(fmt::format("{}", value));
        }
        return *this;
    };

    std::string &finish() {
        if (!hasMembers) {
            repr.append("{");
        }
        repr.append("}");
        return repr;
    }

 private:
    std::string repr;
    bool hasMembers = false;
};

}
#endif //CRAYG_TOSTRINGHELPER_H
