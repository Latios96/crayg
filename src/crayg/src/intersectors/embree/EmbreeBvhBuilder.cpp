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
            embreeBvh->geomIdToSceneObject[geomId] = i;
            rtcReleaseGeometry(mesh);
        }
    }

    rtcCommitScene(rtcScene);

    return embreeBvh;
}
} // crayg