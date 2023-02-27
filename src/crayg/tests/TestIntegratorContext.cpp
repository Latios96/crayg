#include "integrators/AbstractIntegrator.h"
#include "integrators/IntegratorContext.h"
#include <catch2/catch.hpp>
#include <fakeit.hpp>

namespace crayg {

TEST_CASE("IntegratorContext::integrateRay") {

    fakeit::Mock<AbstractIntegrator> mockAbstractIntegrator;
    fakeit::When(Method(mockAbstractIntegrator, integrate)).AlwaysReturn();

    IntegratorContext integratorContext(mockAbstractIntegrator.get(), 0);
    Ray ray({}, {});

    SECTION("should increase recursion depth by one") {
        integratorContext.integrateRay(ray);

        fakeit::Verify(Method(mockAbstractIntegrator, integrate).Using(ray, 1));
    }
}

}