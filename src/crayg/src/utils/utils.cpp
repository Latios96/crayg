#include "utils.h"
#include <boost/algorithm/string/trim_all.hpp>

namespace crayg {

std::string stripCommentFromLine(std::string line) {
    auto commentPosition = line.find('#');
    if (commentPosition != std::string::npos) {
        line = line.substr(0, commentPosition);
    }
    boost::algorithm::trim_all(line);
    return line;
}

}
