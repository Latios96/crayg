//
// Created by Jan on 21.10.2020.
//

#include "ImageBucketSequences.h"
int ImageBucketSequences::fitImage(int pos, int bucketWidth, int dimension) {
    if (pos + bucketWidth > dimension) {
        return dimension - pos;
    }
    return bucketWidth;
}
