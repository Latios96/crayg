//
// Created by Jan Honsbrok on 09.10.18.
//

#include <catch.hpp>
#include <Scene.h>
#include <prims/Stage.h>
#include <prims/Prim.h>


TEST_CASE("createStage", "[Stage]"){
    Stage stage;

}
TEST_CASE("correctPrimAttributeCount", "[Stage]") {
    Stage stage;

    SECTION("emptyScene") {
        StageStats stats = stage.getStats();
        REQUIRE(stats.primCount == 0);
        REQUIRE(stats.attributeCount == 0);
    }

    SECTION("correctAttributeCount") {
        stage.createIntAttributeImpl();
        StageStats stats = stage.getStats();
        REQUIRE(stats.attributeCount == 1);
    }
    SECTION("correctAttributeCount") {
        Prim::definePrim("/some_path", stage);
        StageStats stats = stage.getStats();
        REQUIRE(stats.primCount == 1);
    }

    SECTION("createAttributeImpl") {
        int oldAttributeCount = stage.getStats().attributeCount;

        AttributeImpl<int> *impl = stage.createIntAttributeImpl();

        // attribute count should be increased by one
        REQUIRE(stage.getStats().attributeCount == oldAttributeCount + 1);
    }

    SECTION("createPrimMap") {
        int oldPrimCount = stage.getStats().primCount;

        auto primMap = stage.createPrimMap("some_path");

        REQUIRE(primMap != nullptr);
        REQUIRE(stage.getStats().primCount == oldPrimCount + 1);
    }
}

