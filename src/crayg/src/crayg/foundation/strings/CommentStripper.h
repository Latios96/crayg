#pragma once

#include <string>

namespace crayg {
class CommentStripper {
  public:
    static std::string stripCommentFromLine(std::string line);
};

}
