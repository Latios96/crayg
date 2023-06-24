#include "EmbreeBvhBuilder.h"

#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "utils/StopWatch.h"

namespace crayg {
EmbreeBvhBuilder::EmbreeBvhBuilder(const Scene &scene) : scene(scene) {
}

unsigned int addTriangleMesh(RTCDevice device, RTCScene rtcScene, const TriangleMesh &triangleMesh) {
    RTCGeometry mesh = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

    rtcSetSharedGeometryBuffer(mesh, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, triangleMesh.points.data(), 0,
                               sizeof(Vector3f), triangleMesh.points.size());
    rtcSetSharedGeometryBuffer(mesh, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, triangleMesh.faceVertexIndices.data(),
                               0, sizeof(TriangleMesh::FaceVertexIndices), triangleMesh.faceVertexIndices.size());

    rtcCommitGeometry(mesh);
    unsigned int geomId = rtcAttachGeometry(rtcScene, mesh);
    rtcReleaseGeometry(mesh);
    return geomId;
}

unsigned int addSphere(RTCDevice device, RTCScene rtcScene, const std::shared_ptr<Sphere> &sphere) {
    RTCGeometry embreeSphere = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_SPHERE_POINT);

    auto embreeSphereBuffer = (float *)rtcSetNewGeometryBuffer(embreeSphere, RTC_BUFFER_TYPE_VERTEX, 0,
                                                               RTC_FORMAT_FLOAT4, 4 * sizeof(float), 1);
    const Vector3f &position = sphere->getPosition();
    embreeSphereBuffer[0] = position.x;
    embreeSphereBuffer[1] = position.y;
    embreeSphereBuffer[2] = position.z;
    embreeSphereBuffer[3] = sphere->getRadius();

    rtcCommitGeometry(embreeSphere);
    unsigned int geomId = rtcAttachGeometry(rtcScene, embreeSphere);
    rtcReleaseGeometry(embreeSphere);
    return geomId;
}

RTCScene buildFromSceneObjects(RTCDevice device, const std::vector<std::shared_ptr<SceneObject>> &objects,
                               GeomToSceneObject &geomIdToSceneObject) {
    RTCScene rtcScene = rtcNewScene(device);

    for (unsigned int i = 0; i < objects.size(); i++) {
        auto &sceneObject = objects[i];
        if (sceneObject->getType() == "TriangleMesh") {
            auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, *triangleMesh);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, TRIANGLE_MESH);
        } else if (sceneObject->getType() == "SubdivisionSurfaceMesh") {
            auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, subdivisionSurfaceMesh->triangleMesh);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, SUBDIVISION_SURFACE_MESH);
        } else if (sceneObject->getType() == "Sphere") {
            auto sphere = std::dynamic_pointer_cast<Sphere>(sceneObject);
            unsigned int geomId = addSphere(device, rtcScene, sphere);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, EmbreePrimitiveType::SPHERE);
        }
    }

    rtcCommitScene(rtcScene);

    return rtcScene;
}

std::unique_ptr<EmbreeBvh> EmbreeBvhBuilder::build() const {
    InformativeScopedStopWatch informativeScopedStopWatch("Building Embree BVH");
    auto embreeBvh = std::make_unique<EmbreeBvh>();

    RTCDevice device = rtcNewDevice(nullptr);

    RTCScene rtcScene = buildFromSceneObjects(device, scene.objects, embreeBvh->geomIdToSceneObject);
    embreeBvh->rtcScene = rtcScene;

    return embreeBvh;
}

} // crayg