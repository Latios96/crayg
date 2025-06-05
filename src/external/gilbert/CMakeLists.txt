set(gilbert_sources gilbert.h)

add_library(gilbert STATIC ${gilbert_sources})
set_target_properties(gilbert PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(gilbert PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
