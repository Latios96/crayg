//
// Created by Jan Honsbrok on 01.10.19.
//

#include <spdlog/sinks/stdout_color_sinks.h>
#include "KnipserApp.h"

int main(int argc, char **argv) {
    auto console = spdlog::stdout_color_mt("console");
    KNIPSER_MAIN;
}