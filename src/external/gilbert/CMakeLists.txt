add_library(gilbert INTERFACE)
set_target_properties(gilbert PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(gilbert INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
