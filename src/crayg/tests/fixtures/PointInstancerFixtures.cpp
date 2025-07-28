#include "PointInstancerFixtures.h"
#include "SubdivisionSurfaceMeshFixtures.h"
#include "TriangleMeshFixtures.h"
#include "scene/primitives/Sphere.h"
#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"

namespace crayg {

void PointInstancerFixtures::createInstancerWithSingleTriangleProtoType(PointInstancer &pointInstancer) {
    auto triangleMesh = std::dynamic_pointer_cast<SceneObject>(TriangleMeshFixtures::createPrimVarFixtureMesh());
    createInstancerWithSingleProtoType(pointInstancer, triangleMesh);
}

void PointInstancerFixtures::createInstancerWithSingleSphereProtoType(PointInstancer &pointInstancer) {
    auto sphere = std::dynamic_pointer_cast<SceneObject>(std::make_shared<Sphere>());
    createInstancerWithSingleProtoType(pointInstancer, sphere);
}

void PointInstancerFixtures::createInstancerWithSingleSubdivisionSurfaceMeshProtoType(PointInstancer &pointInstancer) {
    auto subdMesh = std::make_shared<SubdivisionSurfaceMesh>();
    SubdivisionSurfaceMeshFixtures::createUnitPlane(*subdMesh);
    auto sceneObject = std::dynamic_pointer_cast<SceneObject>(subdMesh);
    createInstancerWithSingleProtoType(pointInstancer, sceneObject);
}

void PointInstancerFixtures::createInstancerWithSingleProtoType(PointInstancer &pointInstancer,
                                                                std::shared_ptr<SceneObject> &sceneObject) {
    pointInstancer.ids.push_back(0);
    pointInstancer.protoIndices.push_back(0);
    pointInstancer.transforms.emplace_back();
    auto proto = std::make_shared<PointInstancer::Prototype>();
    proto->members.push_back(sceneObject);
    pointInstancer.protos.push_back(proto);
}

}