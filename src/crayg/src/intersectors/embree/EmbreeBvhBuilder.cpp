#include "EmbreeBvhBuilder.h"

namespace crayg {
EmbreeBvhBuilder::EmbreeBvhBuilder(const Scene &scene) : scene(scene) {

}
std::unique_ptr<EmbreeBvh> EmbreeBvhBuilder::build() const {
    InformativeScopedStopWatch informativeScopedStopWatch("Building Embree BVH");
    auto embreeBvh = std::make_unique<EmbreeBvh>();

    RTCDevice device = rtcNewDevice(nullptr);

    RTCScene rtcScene = rtcNewScene(device);
    embreeBvh->rtcScene = rtcScene;

    for (unsigned int i = 0; i < scene.objects.size(); i++) {
        auto &sceneObject = scene.objects[i];
        if (sceneObject->getType() == "TriangleMesh") {
            auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
            RTCGeometry mesh = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

            rtcSetSharedGeometryBuffer(mesh,
                                       RTC_BUFFER_TYPE_VERTEX,
                                       0, RTC_FORMAT_FLOAT3,
                                       triangleMesh->points.data(),
                                       0, sizeof(Vector3f),
                                       triangleMesh->points.size());
            rtcSetSharedGeometryBuffer(mesh,
                                       RTC_BUFFER_TYPE_INDEX,
                                       0, RTC_FORMAT_UINT3,
                                       triangleMesh->faceVertexIndices.data(),
                                       0,
                                       sizeof(TriangleMesh::FaceVertexIndices),
                                       triangleMesh->faceVertexIndices.size());

            rtcCommitGeometry(mesh);
            unsigned int geomId = rtcAttachGeometry(rtcScene, mesh);
            embreeBvh->geomIdToSceneObject[geomId] = std::make_pair(i, EmbreePrimitiveType::TRIANGLE);
            rtcReleaseGeometry(mesh);
        }
        else if(sceneObject->getType() == "Sphere"){
            auto sphere = std::dynamic_pointer_cast<Sphere>(sceneObject);
            RTCGeometry embreeSphere = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_SPHERE_POINT);

            auto embreeSphereBuffer = (float*) rtcSetNewGeometryBuffer(embreeSphere, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT4,4*sizeof(float), 1);
            const Vector3f &position = sphere->getPosition();
            embreeSphereBuffer[0] = position.x;
            embreeSphereBuffer[1] = position.y;
            embreeSphereBuffer[2] = position.z;
            embreeSphereBuffer[3] = sphere->getRadius();

            rtcCommitGeometry(embreeSphere);
            unsigned int geomId = rtcAttachGeometry(rtcScene, embreeSphere);
            embreeBvh->geomIdToSceneObject[geomId] = std::make_pair(i, EmbreePrimitiveType::SPHERE);
            rtcReleaseGeometry(embreeSphere);
        }
    }

    rtcCommitScene(rtcScene);

    return embreeBvh;
}
} // crayg