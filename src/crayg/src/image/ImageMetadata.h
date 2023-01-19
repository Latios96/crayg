#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEMETADATA_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEMETADATA_H_

#include <variant>
#include <string>
#include <unordered_map>
#include <chrono>
#include <ostream>
#include <fmt/format.h>

namespace crayg {

typedef std::variant<std::string, int, float, std::chrono::seconds> ImageMetadataValue;

class ImageMetadataTokens {
 public:
    static const std::string RENDER_TIME;
    static const std::string RENDER_TIME_SECONDS;
    static const std::string CRAYG_VERSION;
    static const std::string COMPUTER_NAME;
    static const std::string CPU;
    static const std::string RENDER_SETTINGS_INTEGRATOR;
    static const std::string RENDER_SETTINGS_INTERSECTOR;
    static const std::string RENDER_SETTINGS_MAX_SAMPLES;
};

class ImageMetadata {
 public:
    template<typename T>
    void write(const std::string &name, const T &value) {
        values[name] = value;
    }

    ImageMetadataValue readValue(const std::string &name) {
        return values[name];
    }
    template<typename T>
    T read(const std::string &name) {
        return std::get<T>(values[name]);
    }

    bool has(const std::string &name) {
        return values.find(name) != values.end();
    }

    auto begin() const {
        return values.begin();
    }
    auto end() const {
        return values.end();
    }

    bool operator==(const ImageMetadata &rhs) const {
        return values == rhs.values;
    }
    bool operator!=(const ImageMetadata &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const ImageMetadata &metadata) {
        os << "values: ";
        for (auto &v: metadata) {
            os << fmt::format("{}={}", v.first, v.second);
        }
        return os;
    }

 private:
    std::unordered_map<std::string, ImageMetadataValue> values;
};

} // crayg

template<>
struct fmt::formatter<crayg::ImageMetadataValue> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(crayg::ImageMetadataValue const &imageMetadataValue, FormatContext &ctx) {
        if (std::holds_alternative<std::string>(imageMetadataValue)) {
            return fmt::format_to(ctx.out(), "{}", std::get<std::string>(imageMetadataValue));
        } else if (std::holds_alternative<int>(imageMetadataValue)) {
            return fmt::format_to(ctx.out(), "{}", std::get<int>(imageMetadataValue));
        } else if (std::holds_alternative<float>(imageMetadataValue)) {
            return fmt::format_to(ctx.out(), "{}", std::get<float>(imageMetadataValue));
        } else if (std::holds_alternative<std::chrono::seconds>(imageMetadataValue)) {
            return fmt::format_to(ctx.out(), "{}s", std::get<std::chrono::seconds>(imageMetadataValue).count());
        }
    };
};

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGEMETADATA_H_
