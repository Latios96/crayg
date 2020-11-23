//
// Created by Jan on 23.11.2020.
//

#include "ImagePathResolver.h"
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <fmt/format.h>

std::string ImagePathResolver::resolve(const std::string &pathTemplate) const {
    const boost::filesystem::path
        boostPathTemplate = boost::filesystem::absolute(boost::filesystem::path(pathTemplate));
    const boost::filesystem::path target_path(boostPathTemplate.parent_path());
    const boost::regex my_filter(boostPathTemplate.filename().string());

    int frameNumber = 1;

    for (const auto &entry : boost::filesystem::directory_iterator(target_path)) {
        if (!boost::filesystem::is_regular_file(entry.status())) continue;
        boost::smatch what;
        if (!boost::regex_match(boost::regex_replace(entry.path().string(), boost::regex("\.#\."), ".+"),
                                what,
                                my_filter))
            continue;
        int f = parseImageNumber(entry.path().string());
        if (f > frameNumber) {
            frameNumber = f;
        }
    }
    return boost::regex_replace(pathTemplate, boost::regex("\.#\."), fmt::format(".{:0>4}.", frameNumber));
}
int ImagePathResolver::parseImageNumber(const std::string path) const {
    boost::smatch what;
    if (!boost::regex_search(path, what, boost::regex("\\.(\\d+)\\."))) {
        return -1;
    }
    const auto str = what[1].str();
    return std::stoi(str);
}

