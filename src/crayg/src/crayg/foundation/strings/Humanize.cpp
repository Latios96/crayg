#include "Humanize.h"

#include <cmath>
#include <fmt/format.h>
#include <vector>

namespace crayg {

static std::vector<std::string> fileSizeUnits = {
    "Bytes", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB", "RB", "QB",
};

std::string Humanize::naturalFileSize(size_t bytes) {
    if (bytes == 1) {
        return "1 Byte";
    }

    const size_t base = 1000;
    int unitIndex = 0;
    for (int i = 0; i < fileSizeUnits.size(); i++) {
        size_t unit = std::pow(base, i + 1);
        if (bytes < unit) {
            unitIndex = i;
            break;
        }
    }

    if (unitIndex == 0) {
        return fmt::format("{} Bytes", bytes);
    }

    double sizeInUnit = bytes / (std::pow(base, unitIndex));
    return fmt::format("{:.1f} {}", sizeInUnit, fileSizeUnits[unitIndex]);
}

std::string Humanize::naturalDuration(std::chrono::seconds seconds) {
    std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(seconds);
    seconds -= hours;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
    seconds -= minutes;

    int hoursCount = hours.count();
    int minutesCount = minutes.count();
    std::size_t secondsCount = seconds.count();

    std::string result;

    if (hoursCount != 0) {
        result += (result.empty() ? "" : " ") + fmt::format("{} hour{}", hoursCount, hoursCount == 1 ? "" : "s");
    }
    if (minutesCount != 0) {
        result += (result.empty() ? "" : " ") + fmt::format("{} minute{}", minutesCount, minutesCount == 1 ? "" : "s");
    }
    if (secondsCount != 0) {
        result += (result.empty() ? "" : " ") + fmt::format("{} second{}", secondsCount, secondsCount == 1 ? "" : "s");
    }
    if (secondsCount < 1 && hoursCount == 0 && minutesCount == 0) {
        return "less than one second";
    }
    return result;
}
}