#include "LensMaterial.h"
#include "crayg/foundation/exceptions/Exceptions.h"
#include "crayg/foundation/logging/Logger.h"
#include "crayg/foundation/objects/ToStringHelper.h"
#include <fmt/ranges.h>
#include <pystring.h>

namespace crayg {

LensMaterial::LensMaterial(const LensMaterialId &id, float ior, float abbeNo,
                           const std::array<float, 6> &sellmeierCoefficients)
    : id(id), ior(ior), abbeNo(abbeNo), sellmeierCoefficients(sellmeierCoefficients) {
}

bool LensMaterial::operator==(const LensMaterial &rhs) const {
    return id == rhs.id && ior == rhs.ior && abbeNo == rhs.abbeNo && sellmeierCoefficients == rhs.sellmeierCoefficients;
}

bool LensMaterial::operator!=(const LensMaterial &rhs) const {
    return !(rhs == *this);
}

CRAYG_TO_STRING_HELPER_OSTREAM_IMPL(LensMaterial, id, ior, abbeNo, sellmeierCoefficients);

LensMaterial LensMaterial::createMaterialById(LensMaterialId lensMaterialId) {
    switch (lensMaterialId) {
    case LensMaterialId::UNKNOWN:
        return {};
    case LensMaterialId::AIR:
        return LensMaterial(LensMaterialId::AIR, 1, 0, {0, 0, 0, 0, 0, 0});
#include "materials/LensMaterialConstants_ohara.h"

#include "materials/LensMaterialConstants_schott.h"
    }
    CRAYG_LOG_AND_THROW_RUNTIME_ERROR("Unsupported material id: {}", lensMaterialId);
}

std::optional<LensMaterialId> LensMaterial::findMaterialIdByName(const std::string &searchTerm,
                                                                 const std::vector<LensMaterial> &allMaterials) {
    constexpr auto materialIdNames = magic_enum::enum_names<LensMaterialId>();
    for (auto &materialIdName : materialIdNames) {
        if (pystring::endswith(std::string(materialIdName), searchTerm)) {
            return magic_enum::enum_cast<LensMaterialId>(materialIdName);
        }
    }

    return std::nullopt;
}

std::optional<LensMaterialId> LensMaterial::findMaterialIdByName(const std::string &searchTerm) {
    return findMaterialIdByName(searchTerm, getAllMaterials());
}

std::vector<LensMaterial> collectAllMaterials() {
    constexpr auto materialIds = magic_enum::enum_entries<LensMaterialId>();
    std::vector<LensMaterial> materials;
    materials.reserve(materialIds.size());
    for (auto &materialId : materialIds) {
        if (materialId.first == LensMaterialId::UNKNOWN || materialId.first == LensMaterialId::AIR) {
            continue;
        }
        materials.push_back(LensMaterial::createMaterialById(materialId.first));
    }
    return materials;
}

std::vector<LensMaterial> &LensMaterial::getAllMaterials() {
    static std::vector<LensMaterial> allMaterials = collectAllMaterials();
    return allMaterials;
}

std::vector<LensMaterial> &getAllMaterialsSortedByIor() {
    static std::vector<LensMaterial> allMaterialsSortedByIor = collectAllMaterials();
    std::sort(allMaterialsSortedByIor.begin(), allMaterialsSortedByIor.end(), LensMaterial::compareByIor);
    return allMaterialsSortedByIor;
}

LensMaterial LensMaterial::findMaterialByIorAndAbbe(float ior, float abbeNo, MaterialSearchError *searchError) {
    return LensMaterial::findMaterialByIorAndAbbe(ior, abbeNo, searchError, getAllMaterialsSortedByIor());
}

static const int IOR_WEIGHT = 129;

LensMaterial LensMaterial::findMaterialByIorAndAbbe(float ior, float abbeNo, MaterialSearchError *searchError,
                                                    const std::vector<LensMaterial> &allMaterials) {
    if (ior == 1) {
        if (searchError) {
            searchError->iorError = 0;
            searchError->abbeNoError = 0;
        }
        return createMaterialById(LensMaterialId::AIR);
    }

    float minDistance = std::numeric_limits<float>::max();
    int index = -1;
    for (int i = 0; i < allMaterials.size(); i++) {
        const auto &material = allMaterials[i];
        const float iorDifference = (material.ior - ior) * IOR_WEIGHT;
        const float abbeNoDifference = material.abbeNo - abbeNo;
        const float distance = std::sqrt(iorDifference * iorDifference + abbeNoDifference * abbeNoDifference);
        if (distance < minDistance) {
            minDistance = distance;
            index = i;
        }
    }

    const auto &material = allMaterials[index];
    const float iorDifference = material.ior - ior;
    const float abbeNoDifference = material.abbeNo - abbeNo;
    searchError->iorError = iorDifference;
    searchError->abbeNoError = abbeNoDifference;

    return material;
}

bool LensMaterial::MaterialSearchError::isCriticalError() const {
    return std::abs(iorError) > 0.1 || std::abs(abbeNoError) >= 1;
}
}

CRAYG_FMT_ENUM_FORMATTER_IMPL(crayg::LensMaterialId);
