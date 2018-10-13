//
// Created by Jan Honsbrok on 09.10.18.
//

#include <catch.hpp>
#include <prims/Stage.h>
#include <prims/Prim.h>
#include <prims/SpherePrim.h>


TEST_CASE("createPrim", "[Prim]"){
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
        testPrim.defineAttribute<int>("size", stage);

        // now finally create the test prim
        return testPrim;
    }

    explicit TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap);

    Attribute<int> getSizeAttribute(){
        return getAsAttribute<int>("size");
    }
};
TestPrim::TestPrim(std::map<std::string, GenericAttributeImpl *> *primMap) : Prim(primMap) {}

TEST_CASE("createTestPrim", "[Prim]"){
    Stage stage;

    TestPrim prim = TestPrim::defineTestPrim("some_path", stage);

    prim.getSizeAttribute().setValue(10);
    REQUIRE(prim.getSizeAttribute().getValue() == 10);

}


