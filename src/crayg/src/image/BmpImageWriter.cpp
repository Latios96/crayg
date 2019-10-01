//
// Created by jan on 16.08.18.
//

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "BmpImageWriter.h"
#define FMT_HEADER_ONLY
#include "fmt/format.h"


void BmpImageWriter::writeImage(const Image &image, const std::string imageName){

    // https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries

    const int w = image.getWidth(); /* Put here what ever width you want */
    const int h = image.getHeight(); /* Put here what ever height you want */

    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3 * w*h;  //w is your image width, h is image height, both int
    if (img)
        free(img);
    img = (unsigned char *)malloc(3 * w*h);
    memset(img, 0, sizeof(img));
    int x;
    int y;
    int r;
    int g;
    int b;

    for (int i = 0; i<w; i++)
    {
        for (int j = 0; j<h; j++)
        {
            x = i;
            //y = (h - 1) - j;
            y=j;
            auto values = image.getValue(i,j).getRgbValues();
            r = std::get<0>(values);
            g = std::get<1>(values);
            b = std::get<2>(values);
            
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            img[(x + y*w) * 3 + 2] = (unsigned char)(r);
            img[(x + y*w) * 3 + 1] = (unsigned char)(g);
            img[(x + y*w) * 3 + 0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
    unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
    unsigned char bmppad[3] = { 0,0,0 };

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize >> 8);
    bmpfileheader[4] = (unsigned char)(filesize >> 16);
    bmpfileheader[5] = (unsigned char)(filesize >> 24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w >> 8);
    bmpinfoheader[6] = (unsigned char)(w >> 16);
    bmpinfoheader[7] = (unsigned char)(w >> 24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h >> 8);
    bmpinfoheader[10] = (unsigned char)(h >> 16);
    bmpinfoheader[11] = (unsigned char)(h >> 24);

    f = fopen(imageName.c_str(), "wb");
    if (f){
        fwrite(bmpfileheader, 1, 14, f);
        fwrite(bmpinfoheader, 1, 40, f);
        for (int i = 0; i<h; i++)
        {
            fwrite(img + (w*(h - i - 1) * 3), 3, w, f);
            fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
        }
        fclose(f);
    }
    else{
        // todo throw exeption
        std::cout << fmt::format("Error when opening file  {}\n", imageName);
    }

}

BmpImageWriter::~BmpImageWriter() {

}
