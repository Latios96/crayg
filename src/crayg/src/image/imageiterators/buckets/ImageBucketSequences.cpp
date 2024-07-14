#include "ImageBucketSequences.h"
#include "LineByLineSequence.h"
#include "MortonSequence.h"
#include "SpiralSequence.h"
#include "utils/Exceptions.h"
#include <fmt/format.h>

namespace crayg {
std::vector<ImageBucket> ImageBucketSequences::getSequence(const Resolution &resolution, int bucketWidth,
                                                           BucketSequenceType bucketSequenceType) {
    std::unique_ptr<BucketSequence> bucketSequence = nullptr;
    switch (bucketSequenceType) {
    case BucketSequenceType::LINE_BY_LINE:
        bucketSequence = std::make_unique<LineByLineSequence>(resolution, bucketWidth);
        break;
    case BucketSequenceType::SPIRAL:
        bucketSequence = std::make_unique<SpiralSequence>(resolution, bucketWidth);
        break;
    case BucketSequenceType::MORTON:
        bucketSequence = std::make_unique<MortonSequence>(resolution, bucketWidth);
        break;
    default:
        CRAYG_LOG_AND_THROW(
            std::runtime_error(fmt::format(R"(Unsupported BucketSequenceType : "{}")", bucketSequenceType)));
    }
    return bucketSequence->getTiles();
}
}
