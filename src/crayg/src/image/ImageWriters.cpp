//
// Created by jan on 03/10/2019.
//

#include "ImageWriters.h"
#include "ImageWriter.h"
#include "BmpImageWriter.h"
#include <boost/filesystem.hpp>

bool ImageWriters::writeImage(const Image &image, const std::string &imagePath) {
    boost::filesystem::path path(imagePath);
    std::string extension = path.extension().string();
    std::unique_ptr<ImageWriter> imageWriter;
    if(extension == ".bmp"){
        imageWriter = std::unique_ptr<ImageWriter>(new BmpImageWriter());
    }
    /*else if(extension == "png"){
        imageWriter = std::unique_ptr<ImageWriter>(new BmpImageWriter());
    }*/

    if(!imageWriter){
        return false;
    }

    imageWriter->writeImage(image, imagePath);
    return true;
}
