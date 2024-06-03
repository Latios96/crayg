#pragma once

#include "utils/DtoUtils.h"
#include "utils/EnumUtils.h"
#include <embree3/rtcore.h>
#include <unordered_map>

namespace crayg {

enum class EmbreePrimitiveType { TRIANGLE_MESH, SUBDIVISION_SURFACE_MESH, SPHERE };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::EmbreePrimitiveType);

namespace crayg {

CRAYG_DTO_2(EmbreeMappingEntry, std::uint32_t, sceneObjectIndex, EmbreePrimitiveType, primitiveType)

typedef std::unordered_map<unsigned int, EmbreeMappingEntry> GeomToSceneObject;

struct EmbreeProtoInstanceMappingEntry {
    GeomToSceneObject geomToSceneObject;
    std::uint32_t pointInstancerIndex;
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
