//
// Created by jan on 19/08/2019.
//

#include "ImageComparator.h"
ImageComparator::ImageComparator(const std::string &left, const std::string &right) : left(left), right(right) {}


ImageComparatorResult::ImageComparatorResult(ImageComparatorResultStatus status, float error)
    : status(status), error(error) {}
