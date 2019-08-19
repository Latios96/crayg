//
// Created by jan on 19/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_
#define CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_
#include <string>
enum ImageComparatorResultStatus {
    OK, WARNING, ERROR
};
struct ImageComparatorResult {
 public:
    ImageComparatorResult(ImageComparatorResultStatus status, float error);
    ImageComparatorResultStatus status;
    float error;

    bool isOk(){
        return status == ImageComparatorResultStatus::OK;
    }

    bool isWarning(){
        return status == ImageComparatorResultStatus::WARNING;
    }

    bool isError(){
        return status == ImageComparatorResultStatus::ERROR;
    }
};

class ImageComparator {
 public:
    ImageComparator(const std::string &left, const std::string &right);
    virtual ImageComparatorResult compareImages() = 0;
 private:
    std::string left, right;
};

#endif //CRAYG_SRC_KNIPSER_SRC_IMAGECOMPARATOR_H_
