#include "PixelBuffer.h"
#include "imageiterators/pixels/ImageIterators.h"
#include <utils/Preconditions.h>

namespace crayg {

struct PixelBufferSetValue {
    void operator()(float *data) const {
        if (colorChannelCount == 1) {
            for (int pixelNumber = startPixelNumber; pixelNumber < endPixelNumber; pixelNumber++) {
                data[pixelNumber] = color.r;
            }
            return;
        }

        for (int pixelNumber = startPixelNumber; pixelNumber < endPixelNumber; pixelNumber++) {
            data[pixelNumber * colorChannelCount] = color.r;
            data[pixelNumber * colorChannelCount + 1] = color.g;
            data[pixelNumber * colorChannelCount + 2] = color.b;
        }
    }

    void operator()(uint8_t *data) const {
        const auto values = color.getRgbValues();
        if (colorChannelCount == 1) {
            for (int pixelNumber = startPixelNumber; pixelNumber < endPixelNumber; pixelNumber++) {
                data[pixelNumber] = std::get<0>(values);
            }
            return;
        }
        for (int pixelNumber = startPixelNumber; pixelNumber < endPixelNumber; pixelNumber++) {
            data[pixelNumber * colorChannelCount] = std::get<0>(values);
            data[pixelNumber * colorChannelCount + 1] = std::get<1>(values);
            data[pixelNumber * colorChannelCount + 2] = std::get<2>(values);
        }
    }

    int startPixelNumber;
    int endPixelNumber;
    int colorChannelCount;
    const Color &color;
};

struct PixelBufferGetValue {
    Color operator()(float *data) const {
        if (colorChannelCount == 1) {
            return Color::createGrey(data[pixelNumber]);
        }
        return {data[pixelNumber * colorChannelCount], data[pixelNumber * colorChannelCount + 1],
                data[pixelNumber * colorChannelCount + 2]};
    }

    Color operator()(uint8_t *data) const {
        if (colorChannelCount == 1) {
            return Color::createGrey(static_cast<float>(data[pixelNumber]) / 255.f);
        }
        return Color::fromRGB(data[pixelNumber * colorChannelCount], data[pixelNumber * colorChannelCount + 1],
                              data[pixelNumber * colorChannelCount + 2]);
    }

    int pixelNumber;
    int colorChannelCount;
};

struct PixelBufferFree {
    void operator()(float *data) const {
        delete[] data;
    }

    void operator()(uint8_t *data) const {
        delete[] data;
    }
};

PixelBuffer::PixelBuffer(int width, int height, PixelFormat pixelFormat, int channelCount)
    : width(width), height(height), pixelFormat(pixelFormat), colorChannelCount(channelCount) {
    init(pixelFormat);
}

PixelBuffer::PixelBuffer(const Resolution &resolution, PixelFormat pixelFormat, int channelCount)
    : width(resolution.getWidth()), height(resolution.getHeight()), pixelFormat(pixelFormat),
      colorChannelCount(channelCount) {
    init(pixelFormat);
}

PixelBuffer::PixelBuffer(const PixelBuffer &pixelBuffer)
    : width(pixelBuffer.width), height(pixelBuffer.height), pixelFormat(pixelBuffer.pixelFormat),
      colorChannelCount(pixelBuffer.colorChannelCount) {
    int count = pixelBuffer.pixelCount() * colorChannelCount;

    if (pixelBuffer.pixelFormat == PixelFormat::FLOAT) {
        data = new float[count];
        std::memcpy(std::get<float *>(data), std::get<float *>(pixelBuffer.data),
                    pixelCount() * colorChannelCount * sizeof(float));
    } else if (pixelBuffer.pixelFormat == PixelFormat::UINT8) {
        data = new uint8_t[count];
        std::memcpy(std::get<uint8_t *>(data), std::get<uint8_t *>(pixelBuffer.data),
                    pixelCount() * colorChannelCount * sizeof(uint8_t));
    } else {
        throw std::runtime_error("Unsupported pixel format");
    }
}

std::unique_ptr<PixelBuffer> PixelBuffer::createRgbFloat(const Resolution &resolution) {
    return std::make_unique<PixelBuffer>(resolution, PixelFormat::FLOAT, 3);
}

std::unique_ptr<PixelBuffer> PixelBuffer::createGreyFloat(const Resolution &resolution) {
    return std::make_unique<PixelBuffer>(resolution, PixelFormat::FLOAT, 1);
}

std::unique_ptr<PixelBuffer> PixelBuffer::createRgbUInt8(const Resolution &resolution) {
    return std::make_unique<PixelBuffer>(resolution, PixelFormat::UINT8, 3);
}

std::unique_ptr<PixelBuffer> PixelBuffer::createGreyUInt8(const Resolution &resolution) {
    return std::make_unique<PixelBuffer>(resolution, PixelFormat::UINT8, 1);
}

std::unique_ptr<PixelBuffer> PixelBuffer::createVector3f(const Resolution &resolution) {
    return std::make_unique<PixelBuffer>(resolution, PixelFormat::FLOAT, 3);
}

void PixelBuffer::fill(const Color &color) {
    std::visit(PixelBufferSetValue{0, pixelCount(), colorChannelCount, color}, data);
}

void PixelBuffer::setValue(const Vector2i &pixelPosition, const Color &color) {
    CRAYG_CHECKD_IS_VALID_INDEX(pixelNumber(pixelPosition), width * height * colorChannelCount);
    std::visit(
        PixelBufferSetValue{pixelNumber(pixelPosition), pixelNumber(pixelPosition) + 1, colorChannelCount, color},
        data);
}

Color PixelBuffer::getValue(const Vector2i &pixelPosition) const {
    return std::visit(PixelBufferGetValue{pixelNumber(pixelPosition), colorChannelCount}, data);
}

int PixelBuffer::pixelCount() const {
    return width * height;
}

PixelBuffer::~PixelBuffer() {
    std::visit(PixelBufferFree{}, data);
}

int PixelBuffer::pixelNumber(const Vector2i &pixelPosition) const {
    return (pixelPosition.x + width * pixelPosition.y);
}

void PixelBuffer::init(PixelFormat pixelFormat) {
    int count = pixelCount() * colorChannelCount;
    if (pixelFormat == PixelFormat::FLOAT) {
        data = new float[count];
    } else if (pixelFormat == PixelFormat::UINT8) {
        data = new uint8_t[count];
    } else {
        throw std::runtime_error("Unsupported pixel format");
    }
    std::visit(PixelBufferSetValue{0, pixelCount(), colorChannelCount, Color::createBlack()}, data);
}

int PixelBuffer::getWidth() const {
    return width;
}

int PixelBuffer::getHeight() const {
    return height;
}

Resolution PixelBuffer::getResolution() const {
    return {width, height};
}

int PixelBuffer::getColorChannelCount() const {
    return colorChannelCount;
}

bool PixelBuffer::operator==(const PixelBuffer &rhs) const {
    if (data == rhs.data) {
        return true;
    }
    const bool hasSameSpec = data.index() == rhs.data.index() && colorChannelCount == rhs.colorChannelCount &&
                             width == rhs.width && height == rhs.height;
    if (!hasSameSpec) {
        return false;
    }

    for (auto pixel : ImageIterators::lineByLine(*this)) {
        if (getValue(pixel) != rhs.getValue(pixel)) {
            return false;
        }
    }

    return true;
}

bool PixelBuffer::operator!=(const PixelBuffer &rhs) const {
    return !(rhs == *this);
}

const std::variant<float *, uint8_t *> &PixelBuffer::getData() const {
    return data;
}

bool PixelBuffer::isBlack() const {
    return isColor(Color::createBlack());
}

bool PixelBuffer::isWhite() const {
    return isColor(Color::createWhite());
}

bool PixelBuffer::isColor(const Color &color) const {
    for (auto pixel : ImageIterators::lineByLine(*this)) {
        if (getValue(pixel) != color) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const PixelBuffer &buffer) {
    os << ToStringHelper("PixelBuffer")
              .addMember("width", buffer.width)
              .addMember("height", buffer.height)
              .addMember("colorChannelCount", buffer.colorChannelCount)
              .addMember("pixelFormat", buffer.data.index() == 0 ? "FLOAT" : "UINT8")
              .finish();
    return os;
}

PixelFormat PixelBuffer::getPixelFormat() const {
    return pixelFormat;
}

void PixelBuffer::addToPixel(const Vector2i &pixelPosition, const Color &color) {
    const Color currentColor = getValue(pixelPosition);
    setValue(pixelPosition, currentColor + color);
}

void PixelBuffer::dividePixel(const crayg::Vector2i &pixelPosition, float value) {
    const Color currentColor = getValue(pixelPosition);
    setValue(pixelPosition, currentColor / value);
}

} // crayg