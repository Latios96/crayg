#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELBUFFER_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELBUFFER_H_

#include <variant>
#include <memory>
#include <ostream>
#include "basics/Resolution.h"
#include "basics/Color.h"
#include "PixelPosition.h"

namespace crayg {

enum PixelFormat {
    FLOAT,
    UINT8
};

class PixelBuffer {
 public:
    PixelBuffer(int width, int height, PixelFormat pixelFormat, int channelCount);
    PixelBuffer(const Resolution &resolution, PixelFormat pixelFormat, int channelCount);
    PixelBuffer(const PixelBuffer &pixelBuffer);
    static std::unique_ptr<PixelBuffer> createRgbFloat(const Resolution &resolution);
    static std::unique_ptr<PixelBuffer> createGreyFloat(const Resolution &resolution);
    static std::unique_ptr<PixelBuffer> createRgbUInt8(const Resolution &resolution);
    static std::unique_ptr<PixelBuffer> createGreyUInt8(const Resolution &resolution);
    static std::unique_ptr<PixelBuffer> createVector3f(const Resolution &resolution);
    void fill(const Color &color);
    void setValue(const PixelPosition &pixelPosition, const Color &color);
    Color getValue(const PixelPosition &pixelPosition) const;
    bool isBlack() const;
    bool isWhite() const;
    bool isColor(const Color &color) const;
    int pixelCount() const;
    int getWidth() const;
    int getHeight() const;
    Resolution getResolution() const;
    int getColorChannelCount() const;
    const std::variant<float *, uint8_t *> &getData() const;
    bool operator==(const PixelBuffer &rhs) const;
    bool operator!=(const PixelBuffer &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const PixelBuffer &buffer);
    ~PixelBuffer();
 private:
    int pixelNumber(const PixelPosition &pixelPosition) const;
    void init(PixelFormat pixelFormat);

    std::variant<float *, uint8_t *> data;
    PixelFormat pixelFormat;
    int colorChannelCount;
    int width, height;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELBUFFER_H_
