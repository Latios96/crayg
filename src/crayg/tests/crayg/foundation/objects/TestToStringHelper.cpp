#include "crayg/foundation/objects/ToStringHelper.h"

#include <catch2/catch.hpp>
#include <ostream>

namespace crayg {

TEST_CASE("ToStringHelper", "[ToStringHelper]") {
    std::ostringstream os;
    ToStringHelper helper(os, "TestClass");

    SECTION("emptyClass") {
        helper.finish();
        REQUIRE(os.str() == "TestClass{}");
    }

    SECTION("oneMember") {
        helper.addMember("myMember", 1).finish();
        REQUIRE(os.str() == "TestClass{myMember=1}");
    }

    SECTION("twoMembers") {
        helper.addMember("myMember", 1).addMember("myMember2", 2).finish();
        REQUIRE(os.str() == "TestClass{myMember=1,myMember2=2}");
    }
}

namespace tostringhelpertests {

struct Example {
    std::string name;
    int a;

    friend std::ostream &operator<<(std::ostream &os, const Example &obj);
};

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(Example, name, a);

TEST_CASE("ToStringHelper macros", "[ToStringHelper]") {
    Example obj{"test", 42};

    SECTION("should generate correct ToStringHelper") {
        std::ostringstream os;

        CRAYG_TO_STRING_HELPER(os, Example, name, a);

        REQUIRE(os.str() == "Example{name=test,a=42}");
    }

    SECTION("should generate correct implementation of ostream operator") {
        std::ostringstream os;

        os << obj;

        REQUIRE(os.str() == "Example{name=test,a=42}");
    }
}

}

}
