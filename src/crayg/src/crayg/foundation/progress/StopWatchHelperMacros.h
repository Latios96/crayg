#pragma once

#include "StopWatch.h"
#include <source_location>

#define CRAYG_SCOPED_STOP_WATCH_S                                                                                      \
    ScopedStopWatch __scoped_stop_watch(std::source_location::current().function_name(),                               \
                                        StopWatchReportFormat::SECONDS);
#define CRAYG_SCOPED_STOP_WATCH_MS                                                                                     \
    ScopedStopWatch __scoped_stop_watch(std::source_location::current().function_name(),                               \
                                        StopWatchReportFormat::MILLISECONDS);
#define CRAYG_SCOPED_STOP_WATCH_HUMAN                                                                                  \
    ScopedStopWatch __scoped_stop_watch(std::source_location::current().function_name(), StopWatchReportFormat::HUMAN);