//
// Created by Jan Honsbrok on 01.10.19.
//
#include "Logger.h"
#include "KnipserApp.h"

int main(int argc, char **argv) {
    Logger::initialize();
    KNIPSER_MAIN;
}