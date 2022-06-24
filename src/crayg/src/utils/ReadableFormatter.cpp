#include <fmt/format.h>
#include "ReadableFormatter.h"

std::string ReadableFormatter::formatDuration(std::chrono::seconds seconds) {
    std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(seconds);
    seconds -= hours;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
    seconds -= minutes;

    int hoursCount = hours.count();
    int minutesCount = minutes.count();
    int secondsCount = seconds.count();

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
