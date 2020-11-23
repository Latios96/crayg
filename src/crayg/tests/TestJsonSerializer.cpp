//
// Created by Jan on 14.11.2020.
//
#include <catch2/catch.hpp>
#include <scene/Scene.h>
#include <sceneIO/write/json/JsonSerializer.h>
#include <memory>
#include <sstream>
#include <sceneIO/write/SceneWriter.h>

namespace crayg {

TEST_CASE("should write empty scene as expected") {
    Scene scene;

    std::shared_ptr<std::ostringstream> px = std::make_shared<std::ostringstream>();
    auto stream = std::shared_ptr<std::ostream>(px);
    JsonSerializer serializer(stream);
    SceneWriter sceneWriter(scene, serializer);
    sceneWriter.write();

    REQUIRE(px->str() == R"({
    "SceneObjects": [],
    "RenderSettings": {
        "width": 0,
        "height": 0,
        "maxSamples": 4
    }
})");
}

class TestObjectWithAllTypes : public SceneObject {
 public:
    Vector3f getNormal(Vector3f point) override {
        return Vector3f();
    }
    Intersection intersect(Ray ray) override {
        return Intersection();
    }
    bool isIntersecting(Ray ray) override {
        return false;
    }
    void serialize(Serializer &serializer) override {
        serializer.writeInt("int", 0);
        serializer.writeFloat("float", 0.0);
        serializer.writeVector3f("vector3f", Vector3f());
        serializer.writeString("string", "mystring");
        serializer.writeType("mytype");
        std::vector<float> floatVec({0, 0, 0});
        serializer.writeFloatArray("floatArray", floatVec);
        std::vector<int> intVec({0, 0, 0});
        serializer.writeIntArray("intArray", intVec);
        serializer.writeMatrix4x4f("matrix4x4", Matrix4x4f());
        std::vector<Vector3f> vector3fVec({{1, 2, 3}, {4, 5, 6}});
        serializer.writeVector3fArray("vec3fArray", vector3fVec);
        serializer.writeColor("color", Color(1, 2, 3));
    }
};

TEST_CASE("should write scene with objects and camera as expected") {
    Scene scene;

    std::shared_ptr<TestObjectWithAllTypes> testObject = std::make_shared<TestObjectWithAllTypes>();
    scene.addObject(testObject);

    std::shared_ptr<std::ostringstream> px = std::make_shared<std::ostringstream>();
    auto stream = std::shared_ptr<std::ostream>(px);
    JsonSerializer serializer(stream);
    SceneWriter sceneWriter(scene, serializer);
    sceneWriter.write();

    REQUIRE(px->str() == R"({
    "SceneObjects": [
        {
            "int": 0,
            "float": 0.0,
            "vector3f": [
                0.0,
                0.0,
                0.0
            ],
            "string": "mystring",
            "type": "mytype",
            "floatArray": [
                0.0,
                0.0,
                0.0
            ],
            "intArray": [
                0,
                0,
                0
            ],
            "matrix4x4": [
                1.0,
                0.0,
                0.0,
                0.0,
                0.0,
                1.0,
                0.0,
                0.0,
                0.0,
                0.0,
                1.0,
                0.0,
                0.0,
                0.0,
                0.0,
                1.0
            ],
            "vec3fArray": [
                [
                    1.0,
                    2.0,
                    3.0
                ],
                [
                    4.0,
                    5.0,
                    6.0
                ]
            ],
            "color": [
                1.0,
                2.0,
                3.0
            ]
        }
    ],
    "RenderSettings": {
        "width": 0,
        "height": 0,
        "maxSamples": 4
    }
})");
}

}
