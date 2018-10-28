//
// Created by Jan Honsbrok on 28.10.18.
//

#include "LineByLineIterator.h"

class ImageIterators{
public:
    static IteratorAdapter<LineByLineIterator> lineByLine(Image& image){
        return {image};
    }
};