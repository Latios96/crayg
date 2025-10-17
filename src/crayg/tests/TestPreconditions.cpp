#include "crayg/foundation/exceptions/Exceptions.h"
#include <../src/crayg/foundation/assertions/Preconditions.h>
#include <basics/Bound2d.h>
#include <basics/Color.h>
#include <basics/Vector3f.h>
#include <basics/Vector3f_formatter.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

namespace crayg {

#define CRAYG_VERIFY_CHECK_FAILS(check)                                                                                \
    try {                                                                                                              \
        check;                                                                                                         \
        REQUIRE(false);                                                                                                \
    } catch (...) {                                                                                                    \
        REQUIRE(true);                                                                                                 \
    }

TEST_CASE("Preconditions:: check unit vector", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3).normalize());
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3)));
    };

#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3).normalize());
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_NORMALIZED_VECTOR(Vector3f(1, 2, 3)));
    };

#endif
}

TEST_CASE("Preconditions:: check array index", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_IS_VALID_INDEX(0, 1);
        CRAYG_CHECK_IS_VALID_INDEX(0, 10);
        CRAYG_CHECK_IS_VALID_INDEX(1, 10);
        CRAYG_CHECK_IS_VALID_INDEX(3, 10);
    };

    SECTION("should fail") {
        const auto testData = GENERATE(table<int, int>({{-1, 0}, {0, 0}, {10, 10}, {11, 10}}));

        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_VALID_INDEX(std::get<0>(testData), std::get<1>(testData)));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_IS_VALID_INDEX(0, 1);
        CRAYG_CHECKD_IS_VALID_INDEX(0, 10);
        CRAYG_CHECKD_IS_VALID_INDEX(1, 10);
        CRAYG_CHECKD_IS_VALID_INDEX(3, 10);
    };

    SECTION("should fail (debug mode)") {
        const auto testData = GENERATE(table<int, int>({{-1, 0}, {0, 0}, {10, 10}, {11, 10}}));

        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_VALID_INDEX(std::get<0>(testData), std::get<1>(testData)));
    };
#endif
}

TEST_CASE("Preconditions:: check nullptr", "[Preconditions]") {

    SECTION("should pass") {
        const auto ptr = std::make_unique<int>();
        CRAYG_CHECK_NOT_NULLPTR(ptr.get());
    };

    SECTION("should fail for variable") {
        int *ptr = nullptr;
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_NULLPTR(ptr));
    };

    SECTION("should fail for nullptr passed directly") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_NULLPTR(nullptr));
    };

#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        const auto ptr = std::make_unique<int>();
        CRAYG_CHECKD_NOT_NULLPTR(ptr.get());
    };

    SECTION("should fail for variable (debug mode)") {
        int *ptr = nullptr;
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_NULLPTR(ptr));
    };

    SECTION("should fail for nullptr passed directly (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_NULLPTR(nullptr));
    };

#endif
}

TEST_CASE("Preconditions:: equals", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_EQUALS(1, 1);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_EQUALS(1, 2));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_EQUALS(1, 1);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_EQUALS(1, 2));
    };
#endif
}

TEST_CASE("Preconditions:: not equals", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_NOT_EQUALS(1, 2);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_EQUALS(1, 1));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_NOT_EQUALS(1, 2);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_EQUALS(1, 1));
    };
#endif
}

TEST_CASE("Preconditions:: greater or equals", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_GREATER_OR_EQUALS(1, 1);
        CRAYG_CHECK_GREATER_OR_EQUALS(2, 1);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_GREATER_OR_EQUALS(0, 1));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_GREATER_OR_EQUALS(1, 1);
        CRAYG_CHECKD_GREATER_OR_EQUALS(2, 1);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_GREATER_OR_EQUALS(0, 1));
    };
#endif
}

TEST_CASE("Preconditions:: greater than", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_GREATER_THAN(2, 1);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_GREATER_THAN(0, 1));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_GREATER_THAN(1, 1));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_GREATER_THAN(2, 1);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_GREATER_THAN(1, 1));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_GREATER_THAN(0, 1));
    };
#endif
}

TEST_CASE("Preconditions:: less or equals", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_LESS_OR_EQUALS(1, 1);
        CRAYG_CHECK_LESS_OR_EQUALS(0, 1);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_LESS_OR_EQUALS(1, 0));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_LESS_OR_EQUALS(1, 1);
        CRAYG_CHECKD_LESS_OR_EQUALS(0, 1);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_LESS_OR_EQUALS(1, 0));
    };
#endif
}

TEST_CASE("Preconditions:: less than", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_LESS_THAN(1, 2);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_LESS_THAN(1, 0));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_LESS_THAN(1, 1));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_LESS_THAN(1, 2);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_LESS_THAN(1, 0));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_LESS_THAN(1, 1));
    };
#endif
}

TEST_CASE("Preconditions:: within range inclusive", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_WITHIN_RANGE_INCLUSIVE(1, 1, 3);
        CRAYG_CHECK_WITHIN_RANGE_INCLUSIVE(3, 1, 3);
        CRAYG_CHECK_WITHIN_RANGE_INCLUSIVE(2, 1, 3);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_WITHIN_RANGE_INCLUSIVE(0, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_WITHIN_RANGE_INCLUSIVE(4, 1, 3));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_WITHIN_RANGE_INCLUSIVE(1, 1, 3);
        CRAYG_CHECKD_WITHIN_RANGE_INCLUSIVE(3, 1, 3);
        CRAYG_CHECKD_WITHIN_RANGE_INCLUSIVE(2, 1, 3);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_WITHIN_RANGE_INCLUSIVE(0, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_WITHIN_RANGE_INCLUSIVE(4, 1, 3));
    };
#endif
}

TEST_CASE("Preconditions:: not within range inclusive", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_NOT_WITHIN_RANGE_INCLUSIVE(0, 1, 3);
        CRAYG_CHECK_NOT_WITHIN_RANGE_INCLUSIVE(4, 1, 3);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_WITHIN_RANGE_INCLUSIVE(1, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_WITHIN_RANGE_INCLUSIVE(3, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_WITHIN_RANGE_INCLUSIVE(2, 1, 3));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_NOT_WITHIN_RANGE_INCLUSIVE(0, 1, 3);
        CRAYG_CHECKD_NOT_WITHIN_RANGE_INCLUSIVE(4, 1, 3);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_WITHIN_RANGE_INCLUSIVE(1, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_WITHIN_RANGE_INCLUSIVE(3, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_NOT_WITHIN_RANGE_INCLUSIVE(2, 1, 3));
    };
#endif
}

TEST_CASE("Preconditions:: within range exclusive", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_WITHIN_RANGE_EXCLUSIVE(2, 1, 3);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_WITHIN_RANGE_EXCLUSIVE(0, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_WITHIN_RANGE_EXCLUSIVE(1, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_WITHIN_RANGE_EXCLUSIVE(3, 1, 3));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_WITHIN_RANGE_EXCLUSIVE(2, 1, 3);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_WITHIN_RANGE_EXCLUSIVE(0, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_WITHIN_RANGE_EXCLUSIVE(1, 1, 3));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_WITHIN_RANGE_EXCLUSIVE(3, 1, 3));
    };
#endif
}

TEST_CASE("Preconditions:: not within range exclusive", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(0, 1, 3);
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(1, 1, 3);
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(3, 1, 3);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(2, 1, 3));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(0, 1, 3);
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(1, 1, 3);
        CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(3, 1, 3);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_NOT_WITHIN_RANGE_EXCLUSIVE(2, 1, 3));
    };
#endif
}

TEST_CASE("Preconditions:: is not NaN", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_IS_NOT_NAN(1.f);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_NOT_NAN(std::nan("")));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_IS_NOT_NAN(1.f);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_NOT_NAN(std::nan("")));
    };
#endif
}

TEST_CASE("Preconditions:: has no NaN", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_HAS_NO_NAN(Vector3f(1, 2, 3));
        CRAYG_CHECK_HAS_NO_NAN(Color(1, 2, 3));
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_HAS_NO_NAN(Vector3f(std::nan(""), 2, 3)));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_HAS_NO_NAN(Color(std::nan(""), 2, 3)));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_HAS_NO_NAN(Vector3f(1, 2, 3));
        CRAYG_CHECKD_HAS_NO_NAN(Color(1, 2, 3));
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_HAS_NO_NAN(Vector3f(std::nan(""), 2, 3)));
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_HAS_NO_NAN(Color(std::nan(""), 2, 3)));
    };
#endif
}

TEST_CASE("Preconditions:: check state", "[Preconditions]") {
    SECTION("should pass") {
        CRAYG_CHECK_STATE(1, 1);
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_STATE(1, 2));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)") {
        CRAYG_CHECKD_STATE(1, 1);
    };

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_STATE(1, 2));
    };
#endif
}

TEST_CASE("Preconditions:: optional has value", "[Preconditions]") {
    std::optional<int> withValue = 1;
    std::optional<int> withoutValue = std::nullopt;

    SECTION("should pass"){CRAYG_CHECK_OPTIONAL_HAS_VALUE(withValue)};

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_OPTIONAL_HAS_VALUE(withoutValue));
    };
#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass (debug mode)"){CRAYG_CHECKD_OPTIONAL_HAS_VALUE(withValue)};

    SECTION("should fail (debug mode)") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_OPTIONAL_HAS_VALUE(withoutValue));
    };
#endif
}

TEST_CASE("Preconditions:: is empty", "[Preconditions]") {
    const std::vector<int> emptyVector;
    const std::vector<int> notEmptyVector(1);
    const std::string emptyStr;
    const std::string notEmptyStr = "test";

    SECTION("should pass for vector") {
        CRAYG_CHECK_IS_EMPTY(emptyVector);
    };
    SECTION("should pass for string") {
        CRAYG_CHECK_IS_EMPTY(emptyStr);
    };

    SECTION("should fail for vector") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_EMPTY(notEmptyVector));
    }

    SECTION("should fail for string") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_EMPTY(notEmptyStr));
    }

#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass for vector") {
        CRAYG_CHECKD_IS_EMPTY(emptyVector);
    };
    SECTION("should pass for string") {
        CRAYG_CHECKD_IS_EMPTY(emptyStr);
    };

    SECTION("should fail for vector") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_EMPTY(notEmptyVector));
    };

    SECTION("should fail for string") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_EMPTY(notEmptyStr));
    };
#endif
}

TEST_CASE("Preconditions:: is not empty", "[Preconditions]") {
    const std::vector<int> emptyVector;
    const std::vector<int> notEmptyVector(1);
    const std::string emptyStr;
    const std::string notEmptyStr = "test";

    SECTION("should pass for vector") {
        CRAYG_CHECK_IS_NOT_EMPTY(notEmptyVector);
    };
    SECTION("should pass for string") {
        CRAYG_CHECK_IS_NOT_EMPTY(notEmptyStr);
    };

    SECTION("should fail for vector") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_NOT_EMPTY(emptyVector));
    };

    SECTION("should fail for string") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_NOT_EMPTY(emptyStr));
    };

#ifdef CRAYG_DEBUG_CHECKS

    SECTION("should pass for vector") {
        CRAYG_CHECKD_IS_NOT_EMPTY(notEmptyVector);
    };
    SECTION("should pass for string") {
        CRAYG_CHECKD_IS_NOT_EMPTY(notEmptyStr);
    };

    SECTION("should fail for vector") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_NOT_EMPTY(emptyVector));
    };

    SECTION("should fail for string") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_NOT_EMPTY(emptyStr));
    };
#endif
}

TEST_CASE("Precondisions:: is within bounds") {

    SECTION("should pass") {
        CRAYG_CHECK_IS_WITHIN_BOUNDS(Vector2i(1, 1), Bounds2di({0, 0}, {2, 2}));
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_WITHIN_BOUNDS(Vector2i(-1, -1), Bounds2di({0, 0}, {2, 2})));
    };

#ifdef CRAYG_DEBUG_CHECKS
    SECTION("should pass") {
        CRAYG_CHECKD_IS_WITHIN_BOUNDS(Vector2i(1, 1), Bounds2di({0, 0}, {2, 2}));
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_WITHIN_BOUNDS(Vector2i(-1, -1), Bounds2di({0, 0}, {2, 2})));
    };
#endif
}

TEST_CASE("Precondisions:: is not within bounds") {

    SECTION("should pass") {
        CRAYG_CHECK_IS_WITHIN_BOUNDS(Vector2i(1, 1), Bounds2di({0, 0}, {2, 2}));
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECK_IS_WITHIN_BOUNDS(Vector2i(-1, -1), Bounds2di({0, 0}, {2, 2})));
    };

#ifdef CRAYG_DEBUG_CHECKS
    SECTION("should pass") {
        CRAYG_CHECKD_IS_WITHIN_BOUNDS(Vector2i(1, 1), Bounds2di({0, 0}, {2, 2}));
    };

    SECTION("should fail") {
        CRAYG_VERIFY_CHECK_FAILS(CRAYG_CHECKD_IS_WITHIN_BOUNDS(Vector2i(-1, -1), Bounds2di({0, 0}, {2, 2})));
    };
#endif
}
}