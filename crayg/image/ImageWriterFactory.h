//
// Created by Jan Honsbrok on 28.10.18.
//

#include "ImageWriter.h"
#include "BmpImageWriter.h"

enum ImageWriterType {BMP};

ImageWriter* createImageWriter(ImageWriterType type){
switch(type){
    case BMP: return new BmpImageWriter;
    default: return new BmpImageWriter;
}
};