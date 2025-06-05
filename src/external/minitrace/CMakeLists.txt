set(minitrace_sources minitrace.h minitrace.c)

add_library(minitrace STATIC ${minitrace_sources})
target_include_directories(minitrace PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
