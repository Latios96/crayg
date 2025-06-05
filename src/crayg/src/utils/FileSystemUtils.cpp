#include "FileSystemUtils.h"
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <text_encoding_detect.h>

namespace crayg {

std::string FileSystemUtils::swapFileExtension(const std::string &path, const std::string &newExtension) {
    auto boostPath = std::filesystem::path(path);
    return boostPath.replace_extension(newExtension).string();
}

bool needsNoConversion(AutoIt::Common::TextEncodingDetect::Encoding encoding) {
    return encoding == AutoIt::Common::TextEncodingDetect::Encoding::None ||
           encoding == AutoIt::Common::TextEncodingDetect::Encoding::ANSI ||
           encoding == AutoIt::Common::TextEncodingDetect::Encoding::ASCII ||
           encoding == AutoIt::Common::TextEncodingDetect::Encoding::UTF8_BOM ||
           encoding == AutoIt::Common::TextEncodingDetect::Encoding::UTF8_NOBOM;
}

std::string utf16ToUtf8(const std::string &bytes) {
    std::u16string utf16_str(reinterpret_cast<const char16_t *>(bytes.data()), bytes.size() / 2);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.to_bytes(utf16_str);
}

std::string FileSystemUtils::readFileAsString(const std::string &path) {
    std::ifstream inputStream(path);
    std::stringstream buffer;
    buffer << inputStream.rdbuf();
    const std::string fileContent = buffer.str();

    AutoIt::Common::TextEncodingDetect detector;
    auto encoding =
        detector.DetectEncoding(reinterpret_cast<const unsigned char *>(fileContent.data()), fileContent.size());
    if (needsNoConversion(encoding)) {
        return fileContent;
    }

    return utf16ToUtf8(fileContent);
}

} // crayg