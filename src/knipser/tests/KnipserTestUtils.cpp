//
// Created by Jan on 25.05.2020.
//

#include "KnipserTestUtils.h"

namespace knipser {

std::string withOsSeperators(std::string str) {
#ifdef WIN32
    boost::algorithm::replace_all(str, "/", "\\");
#endif
    return str;
}

}
