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