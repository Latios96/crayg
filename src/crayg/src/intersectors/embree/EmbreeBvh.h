#pragma once

#include "utils/DtoUtils.h"
#include "utils/EnumUtils.h"
#include <embree3/rtcore.h>
#include <unordered_map>

namespace crayg {

enum class EmbreePrimitiveType { TRIANGLE_MESH, SUBDIVISION_SURFACE_MESH, SPHERE, LIGHT };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::EmbreePrimitiveType);

namespace crayg {

class PointInstancer;

struct EmbreeMappingEntry {
    void *objPtr;
    EmbreePrimitiveType primitiveType;
    EmbreeMappingEntry() : objPtr(nullptr), primitiveType(EmbreePrimitiveType::TRIANGLE_MESH){};
    EmbreeMappingEntry(void *objPtr, EmbreePrimitiveType primitiveType)
        : objPtr(objPtr), primitiveType(primitiveType){};

    bool operator==(const EmbreeMappingEntry &rhs) const {
        return objPtr == rhs.objPtr && primitiveType == rhs.primitiveType;
    }

    bool operator!=(const EmbreeMappingEntry &rhs) const {
        return !(rhs == *this);
    }
};

// todo check for better map impls
typedef std::unordered_map<unsigned int, EmbreeMappingEntry> GeomToSceneObject;

struct EmbreeProtoInstanceMappingEntry {
    GeomToSceneObject geomToSceneObject;
    PointInstancer *pointInstancer;
    std::uint32_t protoId;
};

CRAYG_DTO_2(EmbreeInstanceInfo, std::uint32_t, globalProtoId, std::uint32_t, instanceId);

typedef std::unordered_map<unsigned int, EmbreeInstanceInfo> EmbreeInstanceIdToInstanceInfo;

struct EmbreeBvh {
    RTCDevice rtcDevice;
    RTCScene rtcScene;
    GeomToSceneObject geomIdToSceneObject;
    std::vector<EmbreeProtoInstanceMappingEntry> globalProtoGeomToSceneObject;
    EmbreeInstanceIdToInstanceInfo embreeInstanceIdToInstanceInfo;
    virtual ~EmbreeBvh();
};

} // crayg
