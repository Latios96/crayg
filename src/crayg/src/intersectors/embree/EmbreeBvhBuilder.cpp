#include "EmbreeBvhBuilder.h"

#include "scene/primitives/PointInstancer.h"
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
                               GeomToSceneObject &geomIdToSceneObject,
                               std::vector<EmbreeProtoInstanceMappingEntry> *globalProtoGeomToSceneObject,
                               EmbreeInstanceIdToInstanceInfo *embreeInstanceIdToInstanceInfo);

void addPointInstancer(RTCDevice device, RTCScene rtcScene, std::shared_ptr<PointInstancer> &pointInstancer,
                       unsigned int pointInstancerIndex,
                       std::vector<EmbreeProtoInstanceMappingEntry> *globalProtoGeomToSceneObject,
                       EmbreeInstanceIdToInstanceInfo *embreeInstanceIdToInstanceInfo) {
    std::unordered_map<size_t, size_t> protoIdToGlobalProtoId;
    std::unordered_map<size_t, RTCScene> protoIdToRtcScene;

    for (int protoId = 0; protoId < pointInstancer->protos.size(); protoId++) {
        auto &proto = pointInstancer->protos[protoId];
        EmbreeProtoInstanceMappingEntry embreeInstanceMappingEntry{};
        embreeInstanceMappingEntry.pointInstancerIndex = pointInstancerIndex;
        embreeInstanceMappingEntry.protoId = protoId;
        protoIdToRtcScene[protoId] =
            buildFromSceneObjects(device, proto->members, embreeInstanceMappingEntry.geomToSceneObject, nullptr,
                                  nullptr); // nullptr is ok because we have only single level instancing..

        auto globalProtoId = globalProtoGeomToSceneObject->size();
        globalProtoGeomToSceneObject->push_back(embreeInstanceMappingEntry);
        protoIdToGlobalProtoId[protoId] = globalProtoId;
    }

    for (int instance = 0; instance < pointInstancer->transforms.size(); instance++) {
        auto protoId = pointInstancer->protoIndices[instance];
        RTCGeometry instancedProto = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_INSTANCE);
        rtcSetGeometryInstancedScene(instancedProto, protoIdToRtcScene[protoId]);
        float transform[16];
        auto &matrix = (pointInstancer->transforms[instance]).matrix; // todo rework this
        transform[0] = matrix.values(0, 0);
        transform[1] = matrix.values(1, 0);
        transform[2] = matrix.values(2, 0);
        transform[3] = matrix.values(3, 0);
        transform[4] = matrix.values(0, 1);
        transform[5] = matrix.values(1, 1);
        transform[6] = matrix.values(2, 1);
        transform[7] = matrix.values(3, 1);
        transform[8] = matrix.values(0, 2);
        transform[9] = matrix.values(1, 2);
        transform[10] = matrix.values(2, 2);
        transform[11] = matrix.values(3, 2);
        transform[12] = matrix.values(0, 3);
        transform[13] = matrix.values(1, 3);
        transform[14] = matrix.values(2, 3);
        transform[15] = matrix.values(3, 3);

        rtcSetGeometryTransform(instancedProto, 0, RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR, transform);
        rtcCommitGeometry(instancedProto);
        unsigned int embreeInstanceId = rtcAttachGeometry(rtcScene, instancedProto);
        rtcReleaseGeometry(instancedProto);
        auto globalProtoId = protoIdToGlobalProtoId[protoId];
        (*embreeInstanceIdToInstanceInfo)[embreeInstanceId] = EmbreeInstanceInfo(globalProtoId, instance);
    }
}

RTCScene buildFromSceneObjects(RTCDevice device, const std::vector<std::shared_ptr<SceneObject>> &objects,
                               GeomToSceneObject &geomIdToSceneObject,
                               std::vector<EmbreeProtoInstanceMappingEntry> *globalProtoGeomToSceneObject,
                               EmbreeInstanceIdToInstanceInfo *embreeInstanceIdToInstanceInfo) {
    RTCScene rtcScene = rtcNewScene(device);

    for (unsigned int i = 0; i < objects.size(); i++) {
        auto &sceneObject = objects[i];
        if (sceneObject->getType() == "TriangleMesh") {
            auto triangleMesh = std::dynamic_pointer_cast<TriangleMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, *triangleMesh);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, EmbreePrimitiveType::TRIANGLE_MESH);
        } else if (sceneObject->getType() == "SubdivisionSurfaceMesh") {
            auto subdivisionSurfaceMesh = std::dynamic_pointer_cast<SubdivisionSurfaceMesh>(sceneObject);
            unsigned int geomId = addTriangleMesh(device, rtcScene, subdivisionSurfaceMesh->triangleMesh);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, EmbreePrimitiveType::SUBDIVISION_SURFACE_MESH);
        } else if (sceneObject->getType() == "Sphere") {
            auto sphere = std::dynamic_pointer_cast<Sphere>(sceneObject);
            unsigned int geomId = addSphere(device, rtcScene, sphere);
            geomIdToSceneObject[geomId] = EmbreeMappingEntry(i, EmbreePrimitiveType::SPHERE);
        } else if (sceneObject->getType() == "PointInstancer") {
            auto pointInstancer = std::dynamic_pointer_cast<PointInstancer>(sceneObject);
            addPointInstancer(device, rtcScene, pointInstancer, i, globalProtoGeomToSceneObject,
                              embreeInstanceIdToInstanceInfo);
        }
    }

    rtcCommitScene(rtcScene);

    return rtcScene;
}

std::unique_ptr<EmbreeBvh> EmbreeBvhBuilder::build() const {
    InformativeScopedStopWatch informativeScopedStopWatch("Building Embree BVH");
    auto embreeBvh = std::make_unique<EmbreeBvh>();

    RTCDevice device = rtcNewDevice(nullptr);

    RTCScene rtcScene =
        buildFromSceneObjects(device, scene.objects, embreeBvh->geomIdToSceneObject,
                              &embreeBvh->globalProtoGeomToSceneObject, &embreeBvh->embreeInstanceIdToInstanceInfo);
    embreeBvh->rtcScene = rtcScene;

    return embreeBvh;
}

} // crayg