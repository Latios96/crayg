//
// Created by Jan Honsbrok on 01.11.18.
//

#include <catch.hpp>
#include <scene/Scene.h>
#include <fakeit.hpp>
#include "sceneIO/SceneWriter.h"

TEST_CASE("SceneWriter"){
    Scene scene;

    scene.addObject(new Sphere(Vector3f(1,0,0), 1));
    scene.addObject(new Sphere(Vector3f(-2,0,0), 1));

    fakeit::Mock<SerializerImplementation> mockSerializerImpl;

    fakeit::When(Method(mockSerializerImpl,init)).AlwaysReturn();
    fakeit::When(Method(mockSerializerImpl,startObject)).AlwaysReturn();
    fakeit::When(Method(mockSerializerImpl,endObject)).AlwaysReturn();
    fakeit::When(Method(mockSerializerImpl,finish)).AlwaysReturn();

    fakeit::When(Method(mockSerializerImpl,writeFloat)).AlwaysReturn();
    fakeit::When(Method(mockSerializerImpl,writeVector3f)).AlwaysReturn();
    fakeit::When(Method(mockSerializerImpl,writeType)).AlwaysReturn();


    SceneWriter sceneWriter(scene, mockSerializerImpl.get());

    SECTION("writeSceneCallCountMatchesObjectCound"){
        sceneWriter.write();

        fakeit::Verify(Method(mockSerializerImpl,init)).Exactly(1);
        fakeit::Verify(Method(mockSerializerImpl,startObject)).Exactly(2);
        fakeit::Verify(Method(mockSerializerImpl,endObject)).Exactly(2);
        fakeit::Verify(Method(mockSerializerImpl,finish)).Exactly(1);

    }

}