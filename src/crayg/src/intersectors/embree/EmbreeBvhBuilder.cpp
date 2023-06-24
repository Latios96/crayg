#include "EmbreeBvhBuilder.h"

#include "scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h"
#include "scene/primitives/trianglemesh/TriangleMesh.h"
#include "utils/StopWatch.h"

namespace crayg {
EmbreeBvhBuilder::EmbreeBvhBuilder(const Scene &scene) : scene(scene) {
}

std::unique_ptr<EmbreeBvh> EmbreeBvhBuilder::build() const {
    InformativeScopedStopWatch informativeScopedStopWatch("Building Embree BVH");
    auto embreeBvh = std::make_unique<EmbreeBvh>();

    RTCDevice device = rtcNewDevice(nullptr);
    RTCScene rtcScene = rtcNewScene(device);

    for (unsigned int i = 0; i < scene.objects.size(); i++) {
        auto &sceneObject = scene.objects[i];
        if (sceneObject->getType() == "TriangleMesh") {
            auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, *triangleMesh);
            embreeBvh->geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, TRIANGLE_MESH);
        } else if (sceneObject->getType() == "SubdivisionSurfaceMesh") {
            auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, subdivisionSurfaceMesh->triangleMesh);
            embreeBvh->geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, SUBDIVISION_SURFACE_MESH);
        } else if (sceneObject->getType() == "Sphere") {
            auto sphere = std::dynamic_pointer_cast<Sphere>(sceneObject);
            unsigned int geomId = addSphere(device, rtcScene, sphere);
            embreeBvh->geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, EmbreePrimitiveType::SPHERE);
        }
    }

    rtcCommitScene(rtcScene);

    embreeBvh->rtcScene = rtcScene;

    return embreeBvh;
}

unsigned int EmbreeBvhBuilder::addTriangleMesh(RTCDevice device, RTCScene rtcScene,
                                               const TriangleMesh &triangleMesh) const {
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

unsigned int EmbreeBvhBuilder::addSphere(RTCDevice device, RTCScene rtcScene,
                                         const std::shared_ptr<Sphere> &sphere) const {
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
} // crayg