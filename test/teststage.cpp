//
// Created by Jan Honsbrok on 09.10.18.
//

#include <catch.hpp>
#include <Scene.h>
#include <Stage.h>

TEST_CASE("Stage should be created", "[Stage]"){
    std::unique_ptr<Stage> stage (new Stage());

}
TEST_CASE("Stage stats should return correct count of prims and attributes", "[Stage]"){
    std::unique_ptr<Stage> stage (new Stage());

    SECTION("Empty scene"){
        StageStats stats = stage->getStats();
        REQUIRE(stats.primCount == 0);
        REQUIRE(stats.attributeCount == 0);
    }

    SECTION("Correct attribute count"){
        stage->createIntAttributeImpl();
        StageStats stats = stage->getStats();
        REQUIRE(stats.attributeCount == 1);
    }
    // todo correct prim count

}
TEST_CASE("An AttributeImpl should be created",  "[Stage]"){
    std::unique_ptr<Stage> stage (new Stage());
    int oldAttributeCount = stage->getStats().attributeCount;

    AttributeImpl<int>* impl = stage->createIntAttributeImpl();

    // attribute count should be increased by one
    REQUIRE(stage->getStats().attributeCount == oldAttributeCount+1);
}

TEST_CASE("A Prim should be created",  "[Stage]"){
    std::unique_ptr<Stage> stage (new Stage());
    int oldPrimCount = stage->getStats().primCount;

    auto primMap =  stage->createPrimMap("some_path");

    REQUIRE(primMap != nullptr);
    REQUIRE(stage->getStats().primCount == oldPrimCount+1);
}

