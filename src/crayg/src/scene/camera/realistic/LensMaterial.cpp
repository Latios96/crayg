#include "LensMaterial.h"
#include "utils/ToStringHelper.h"

namespace crayg {

bool NLensMaterial::operator==(const NLensMaterial &rhs) const {
    return id == rhs.id && ior == rhs.ior && abbeNo == rhs.abbeNo && sellmeierCoefficients == rhs.sellmeierCoefficients;
}

bool NLensMaterial::operator!=(const NLensMaterial &rhs) const {
    return !(rhs == *this);
}

NLensMaterial::NLensMaterial(const LensMaterialId &id, float ior, float abbeNo,
                             const std::array<float, 6> &sellmeierCoefficients)
    : id(id), ior(ior), abbeNo(abbeNo), sellmeierCoefficients(sellmeierCoefficients) {
}

std::ostream &operator<<(std::ostream &os, const NLensMaterial &material) {
    os << ToStringHelper("NLensMaterial")
              .addMember("id", material.id)
              .addMember("ior", material.ior)
              .addMember("abbeNo", material.abbeNo)
              .addMember("sellmeierCoefficients",
                         fmt::format("{}, {}, {}, {}, {}, {}", material.sellmeierCoefficients[0],
                                     material.sellmeierCoefficients[1], material.sellmeierCoefficients[2],
                                     material.sellmeierCoefficients[3], material.sellmeierCoefficients[4],
                                     material.sellmeierCoefficients[5]))
              .finish();
    return os;
}

NLensMaterial NLensMaterial::createMaterialById(LensMaterialId lensMaterialId) {
    switch (lensMaterialId) {
    case LensMaterialId::UNKNOWN:
        return {};
#include "materials/LensMaterialConstants_ohara.h"
#include "materials/LensMaterialConstants_schott.h"
    }
    throw std::runtime_error(fmt::format("Unsupported material id: {}", lensMaterialId));
}

std::vector<NLensMaterial> collectAllMaterials() {
    constexpr auto materialIds = magic_enum::enum_entries<LensMaterialId>();
    std::vector<NLensMaterial> materials;
    materials.reserve(materialIds.size());
    for (auto &materialId : materialIds) {
        materials.push_back(NLensMaterial::createMaterialById(materialId.first));
    }
    return materials;
}

std::vector<NLensMaterial> &NLensMaterial::getAllMaterials() {
    static std::vector<NLensMaterial> allMaterials = collectAllMaterials();
    return allMaterials;
}

std::optional<NLensMaterial> NLensMaterial::findMaterialByIorAndAbbe(float ior, float abbeNo) {
    return NLensMaterial::findMaterialByIorAndAbbe(ior, abbeNo, getAllMaterials());
}

template <typename T>
float findElementsWithSmalledDifference(const std::vector<T> &elements, std::vector<T> &elementsWithMinimalError,
                                        const std::function<float(const T &a)> &errorFunc) {
    if (elements.empty()) {
        return 0;
    }
    float minimalError = std::numeric_limits<float>::max();
    int indexOfMinimalError = -1;

    for (int i = 0; i < elements.size(); i++) {
        const float elementError = errorFunc(elements[i]);
        if (elementError < minimalError) {
            minimalError = elementError;
            indexOfMinimalError = i;
        }
    }

    for (int i = indexOfMinimalError; i < elements.size(); i++) {
        const float elementError = errorFunc(elements[i]);
        if (elementError == minimalError) {
            elementsWithMinimalError.push_back(elements[i]);
        }
        if (elementError > minimalError) {
            break;
        }
    }

    for (int i = indexOfMinimalError - 1; i >= 0; i--) {
        const float elementError = errorFunc(elements[i]);
        if (elementError == minimalError) {
            elementsWithMinimalError.push_back(elements[i]);
        }
        if (elementError > minimalError) {
            break;
        }
    }
    return minimalError;
}

std::optional<NLensMaterial> NLensMaterial::findMaterialByIorAndAbbe(float ior, float abbeNo,
                                                                     const std::vector<NLensMaterial> &allMaterials) {
    std::vector<NLensMaterial> iorResults;
    const float minimalIorError = findElementsWithSmalledDifference<NLensMaterial>(
        allMaterials, iorResults, [ior](const NLensMaterial &material) { return std::abs(material.ior - ior); });

    if (minimalIorError > 0.1) {
        return std::nullopt;
    }

    std::sort(iorResults.begin(), iorResults.end(), NLensMaterial::compareByAbbeNo);

    std::vector<NLensMaterial> abbeNoResults;
    const float minimalAbbeNoError = findElementsWithSmalledDifference<NLensMaterial>(
        iorResults, abbeNoResults,
        [abbeNo](const NLensMaterial &material) { return std::abs(material.abbeNo - abbeNo); });
    if (minimalAbbeNoError > 1) {
        return std::nullopt;
    }
    return abbeNoResults[0];
}

}