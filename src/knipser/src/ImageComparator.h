//
// Created by jan on 19/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_
#define CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_

#include <string>


enum ImageComparatorResultStatus {
    OK, WARNING, IMAGE_ERROR
};
struct ImageComparatorResult {
 public:
    ImageComparatorResult(ImageComparatorResultStatus status, float error);
    ImageComparatorResultStatus status;
    float error;

    bool isOk() {
        return status == ImageComparatorResultStatus::OK;
    }

    bool isWarning() {
        return status == ImageComparatorResultStatus::WARNING;
    }

    bool isError() {
        return status == ImageComparatorResultStatus::IMAGE_ERROR;
    }
};

class ImageComparator {
 public:
    ImageComparator(std::string left, std::string right);
    virtual ImageComparatorResult compareImages() = 0;
 protected:
    std::string left, right;
};

class OpenImageIoImageComparator : public ImageComparator {
 public:
    OpenImageIoImageComparator(const std::string &left, const std::string &right);
    ImageComparatorResult compareImages() override;

};

#endif //CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_
