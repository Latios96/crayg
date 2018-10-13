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

// Test Prim
class TestPrim : Prim{
public:
    static TestPrim defineTestPrim(const std::string &path, Stage &stage) {
        // get the prims attribute map
        auto primMap =  stage.createPrimMap(path);

        TestPrim testPrim(primMap);

        // define Attributes
        testPrim.defineIntAttribute("size", stage);

        // now finally create the test prim
        return testPrim;
    }

    explicit TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap);

    Attribute<int> getSizeAttribute(){
        return getAsIntAttribute("size");
    }
};
TestPrim::TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap) : Prim(primMap) {}

TEST_CASE("Define a Test Prim and set / read the test Attribute", "[Prim]"){
    Stage stage;

    TestPrim prim = TestPrim::defineTestPrim("some_path", stage);

    prim.getSizeAttribute().setValue(10);
    REQUIRE(prim.getSizeAttribute().getValue() == 10);

}