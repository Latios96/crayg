//
// Created by jan on 19/08/2019.
//

#include "ImageComparator.h"

#include <utility>
ImageComparator::ImageComparator(std::string left, std::string right)
    : left(std::move(left)), right(std::move(right)) {}

ImageComparatorResult::ImageComparatorResult(ImageComparatorResultStatus status, float error)
    : status(status), error(error) {}

OpenImageIoImageComparator::OpenImageIoImageComparator(const std::string &left, const std::string &right)
    : ImageComparator(left, right) {}
ImageComparatorResult OpenImageIoImageComparator::compareImages() {

    OIIO::ImageBuf leftInput(left);
    OIIO::ImageBuf rightInput(right);

    auto result = OIIO::ImageBufAlgo::compare(leftInput, rightInput, 1, 0.0);
    if (result.error){
        return {ERROR, static_cast<float>(result.maxerror)};
    }
    else{
        return {OK, 0.0};
    }
}
