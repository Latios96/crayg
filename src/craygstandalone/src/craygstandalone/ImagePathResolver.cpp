#include "ImagePathResolver.h"
#include <boost/regex.hpp>
#include <filesystem>
#include <fmt/format.h>
#include <vector>

namespace crayg {

std::filesystem::path ImagePathResolver::resolve(const std::filesystem::path &pathTemplate) {
    const std::filesystem::path boostPathTemplate = std::filesystem::absolute(std::filesystem::path(pathTemplate));
    const std::filesystem::path target_path(boostPathTemplate.parent_path());

    int frameNumber = 0;

    for (const auto &entry : std::filesystem::directory_iterator(target_path)) {
        const bool isRegularFile = std::filesystem::is_regular_file(entry.status());
        const bool isMatching =
            matchesTemplate(std::filesystem::path(pathTemplate).filename().string(), entry.path().filename().string());

        if (!isRegularFile | !isMatching) {
            continue;
        }
        auto parsedFrameNumber = parseImageNumber(entry.path().string());
        if (parsedFrameNumber.has_value()) {
            frameNumber = *parsedFrameNumber;
        }
    }
    return boost::regex_replace(pathTemplate.string(), boost::regex("\\.#\\."),
                                fmt::format(".{:0>4}.", frameNumber + 1));
}

std::optional<int> ImagePathResolver::parseImageNumber(const std::filesystem::path &path) {
    boost::smatch what;
    std::string pathString = path.string();
    if (!boost::regex_search(pathString, what, boost::regex("\\.(\\d+)\\."))) {
        return std::nullopt;
    }
    const auto str = what[1].str();
    return std::stoi(str);
}

bool ImagePathResolver::matchesTemplate(const std::filesystem::path &pathTemplate, const std::filesystem::path &path) {
    boost::smatch what;
    const std::string filenameWithFilter =
        boost::regex_replace(pathTemplate.string(), boost::regex(R"(\.#\.)"), R"(\\.(\\d+)\\.)");
    return boost::regex_search(path.string(), what, boost::regex(filenameWithFilter));
}

}
