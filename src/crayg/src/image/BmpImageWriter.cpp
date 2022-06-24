#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "BmpImageWriter.h"
#include "fmt/format.h"

namespace crayg {

void BmpImageWriter::writeImage(const Image &image, const std::string imageName) {

    // https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

    const int width = image.getWidth();
    const int height = image.getHeight();

    auto *img = (unsigned char *) malloc(3 * width * height);
    memset(img, 0, sizeof(&img));

    int x;
    int y;
    int r;
    int g;
    int b;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x = i;
            y = j;
            auto values = image.getValue(i, j).getRgbValues();
            r = std::get<0>(values);
            g = std::get<1>(values);
            b = std::get<2>(values);

            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            img[(x + y * width) * 3 + 2] = (unsigned char) (r);
            img[(x + y * width) * 3 + 1] = (unsigned char) (g);
            img[(x + y * width) * 3 + 0] = (unsigned char) (b);
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};
    int filesize = 54 + 3 * width * height;

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[4] = (unsigned char) (width);
    bmpinfoheader[5] = (unsigned char) (width >> 8);
    bmpinfoheader[6] = (unsigned char) (width >> 16);
    bmpinfoheader[7] = (unsigned char) (width >> 24);
    bmpinfoheader[8] = (unsigned char) (height);
    bmpinfoheader[9] = (unsigned char) (height >> 8);
    bmpinfoheader[10] = (unsigned char) (height >> 16);
    bmpinfoheader[11] = (unsigned char) (height >> 24);

    FILE *f = fopen(imageName.c_str(), "wb");
    if (f) {
        fwrite(bmpfileheader, 1, 14, f);
        fwrite(bmpinfoheader, 1, 40, f);
        for (int i = 0; i < height; i++) {
            fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
            fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
        }
        fclose(f);
    } else {
        throw std::runtime_error(fmt::format("Error when opening file  {}\n", imageName));
    }

}

BmpImageWriter::~BmpImageWriter() = default;

}