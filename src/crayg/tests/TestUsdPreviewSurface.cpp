#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include "scene/materials/UsdPreviewSurface.h"
#include "integrators/AbstractIntegrator.h"

namespace crayg {

TEST_CASE("UsdPreviewSurface::evaluate") {
    SurfaceInteraction surfaceInteraction({0,0,0},{0,1,0},{{1,1,0},{-1,-1,0}});
    fakeit::Mock<AbstractIntegrator> mockAbstractIntegrator;
    IntegratorContext integratorContext(mockAbstractIntegrator.get(), 0);

    SECTION("should return diffuse Color for only diffuse surface") {
        UsdPreviewSurface usdPreviewSurface(Color::createGrey(0.5f));
        fakeit::When(Method(mockAbstractIntegrator, integrate)).AlwaysReturn();

        const auto result = usdPreviewSurface.evaluate(surfaceInteraction, integratorContext);

        REQUIRE(result == Color::createGrey(0.5f));
        fakeit::Verify(Method(mockAbstractIntegrator, integrate)).Never();
    }

    SECTION("should trace reflection ray and add weighted reflection") {
        UsdPreviewSurface usdPreviewSurface(Color::createBlack());
        usdPreviewSurface.metallic = 0.5;
        fakeit::When(Method(mockAbstractIntegrator, integrate)).Return(Color::createWhite());

        const auto result = usdPreviewSurface.evaluate(surfaceInteraction, integratorContext);

        REQUIRE(result == Color::createGrey(0.5f));
        fakeit::Verify(Method(mockAbstractIntegrator, integrate)).Once();
    }
}

}