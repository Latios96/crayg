#include <Logger.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace crayg {

void Logger::setLevel(LevelEnum level) {
    if (level == LevelEnum::trace) {
        spdlog::set_level(spdlog::level::trace);
    } else if (level == LevelEnum::debug) {
        spdlog::set_level(spdlog::level::debug);
    } else if (level == LevelEnum::info) {
        spdlog::set_level(spdlog::level::info);
    } else if (level == LevelEnum::warn) {
        spdlog::set_level(spdlog::level::warn);
    } else if (level == LevelEnum::err) {
        spdlog::set_level(spdlog::level::err);
    } else if (level == LevelEnum::critical) {
        spdlog::set_level(spdlog::level::critical);
    } else if (level == LevelEnum::off) {
        spdlog::set_level(spdlog::level::off);
    }
}

void Logger::initialize() {
    std::locale::global(std::locale("en_US.UTF-8"));

    std::vector<spdlog::sink_ptr> sinks;
    const auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    sinks.push_back(stdout_sink);

    auto combined_logger = std::make_shared<spdlog::logger>("console", begin(sinks), end(sinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);
    spdlog::flush_on(spdlog::level::info);
}
void Logger::logToFile(const std::string &fileName) {
    const auto file_synk = std::make_shared<spdlog::sinks::basic_file_sink_st>(fileName, true);
    file_synk->set_level(spdlog::level::info);
    spdlog::default_logger()->sinks().push_back(file_synk);
}

}