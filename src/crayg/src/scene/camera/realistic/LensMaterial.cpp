#include "LensMaterial.h"
#include "Logger.h"
#include "utils/ToStringHelper.h"

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

std::ostream &operator<<(std::ostream &os, const LensMaterial &material) {
    os << ToStringHelper("LensMaterial")
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

LensMaterial LensMaterial::createMaterialById(LensMaterialId lensMaterialId) {
    switch (lensMaterialId) {
    case LensMaterialId::UNKNOWN:
        return {};
    case LensMaterialId::AIR:
        return LensMaterial(LensMaterialId::AIR, 1, 0, {0, 0, 0, 0, 0, 0});
#include "materials/LensMaterialConstants_ohara.h"
#include "materials/LensMaterialConstants_schott.h"
    }
    throw std::runtime_error(fmt::format("Unsupported material id: {}", lensMaterialId));
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

LensMaterial LensMaterial::findMaterialByIorAndAbbe(float ior, float abbeNo, MaterialSearchError *searchError,
                                                    const std::vector<LensMaterial> &allMaterials) {
    if (ior == 1) {
        if (searchError) {
            searchError->iorError = 0;
            searchError->abbeNoError = 0;
        }
        return createMaterialById(LensMaterialId::AIR);
    }
    std::vector<LensMaterial> iorResults;
    const float minimalIorError = findElementsWithSmalledDifference<LensMaterial>(
        allMaterials, iorResults, [ior](const LensMaterial &material) { return std::abs(material.ior - ior); });

    std::sort(iorResults.begin(), iorResults.end(), LensMaterial::compareByAbbeNo);

    std::vector<LensMaterial> abbeNoResults;
    const float minimalAbbeNoError = findElementsWithSmalledDifference<LensMaterial>(
        iorResults, abbeNoResults,
        [abbeNo](const LensMaterial &material) { return std::abs(material.abbeNo - abbeNo); });

    if (searchError) {
        searchError->iorError = minimalIorError;
        searchError->abbeNoError = minimalAbbeNoError;
    }

    return abbeNoResults[0];
}

float LensMaterial::getIor(float lambda_nm) const {
    const float lambda_micrometer = lambda_nm / 1000.f;
    float lambdaSquared = lambda_micrometer * lambda_micrometer;
    return std::sqrt(1 + sellmeierTerm(lambdaSquared, 0) + sellmeierTerm(lambdaSquared, 1) +
                     sellmeierTerm(lambdaSquared, 2));
}

float LensMaterial::sellmeierTerm(float lambdaSquared, int index) const {
    return sellmeierCoefficients[index] * lambdaSquared / (lambdaSquared - sellmeierCoefficients[index + 3]);
}

bool LensMaterial::MaterialSearchError::isCriticalError() const {
    return iorError > 0.1 || abbeNoError >= 1;
}
}