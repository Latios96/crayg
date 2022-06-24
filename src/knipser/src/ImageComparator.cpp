#include "ImageComparator.h"

#include <utility>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>

namespace knipser {

ImageComparator::ImageComparator(std::string left, std::string right)
    : left(std::move(left)), right(std::move(right)) {}

ImageComparatorResult::ImageComparatorResult(ImageComparatorResultStatus status, float error)
    : status(status), error(error) {}

OpenImageIoImageComparator::OpenImageIoImageComparator(const std::string &left, const std::string &right)
    : ImageComparator(left, right) {}
ImageComparatorResult OpenImageIoImageComparator::compareImages() {

    OIIO::ImageBuf leftInput(left);
    OIIO::ImageBuf rightInput(right);

    auto result = OIIO::ImageBufAlgo::compare(leftInput, rightInput, 0.5, 0.0);
    if (result.error) {
        return {IMAGE_ERROR, static_cast<float>(result.maxerror)};
    } else {
        return {OK, 0.0};
    }
}

}
