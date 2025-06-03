#include "utils/AtomicFloats.h"
#include <catch2/catch.hpp>
#include <tbb/parallel_for.h>

namespace crayg {

TEST_CASE("AtomicFloats::construct") {
    SECTION("float") {
        AtomicFloat atomicFloat;
        REQUIRE(atomicFloat.get() == 0);
    }

    SECTION("double") {
        AtomicDouble atomicDouble;
        REQUIRE(atomicDouble.get() == 0);
    }
}

TEST_CASE("AtomicFloats::addAtomic") {

    SECTION("should add correctly for float serial") {
        AtomicFloat atomicFloat;

        atomicFloat.atomicAdd(42);
        REQUIRE(atomicFloat.get() == 42);

        atomicFloat.atomicAdd(42);
        REQUIRE(atomicFloat.get() == 84);
    }

    SECTION("should add correctly for float parallel") {
        AtomicFloat atomicFloat;

        tbb::parallel_for(0, 32000, [&atomicFloat](int i) { atomicFloat.atomicAdd(1); });

        REQUIRE(atomicFloat.get() == 32000);
    }

    SECTION("should add correctly for double serial") {
        AtomicDouble atomicDouble;

        atomicDouble.atomicAdd(42);
        REQUIRE(atomicDouble.get() == 42);

        atomicDouble.atomicAdd(42);
        REQUIRE(atomicDouble.get() == 84);
    }

    SECTION("should add correctly for double parallel") {
        AtomicDouble atomicDouble;

        tbb::parallel_for(0, 32000, [&atomicDouble](int i) { atomicDouble.atomicAdd(1); });

        REQUIRE(atomicDouble.get() == 32000);
    }
}

}