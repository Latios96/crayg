//
// Created by Jan Honsbrok on 09.10.18.
//

#include <catch.hpp>
#include <Stage.h>
#include <Prim.h>

TEST_CASE("A prim should be created in the stage for given path", "[Prim]"){
    Stage* stage = new Stage();

    Prim::definePrim("some_path", *stage);

    delete stage;
}

TEST_CASE("Test prim", "[Prim]"){
    Stage* stage = new Stage();

    TestPrim prim = TestPrim::defineTestPrim("some_path", *stage);

    prim.getSizeAttribute().setValue(10);
    REQUIRE(prim.getSizeAttribute().getValue() == 10);


    delete stage;
}