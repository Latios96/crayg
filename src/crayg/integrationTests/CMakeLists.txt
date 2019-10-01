add_executable(crayg-integration-tests main.cpp)
target_link_libraries(crayg-integration-tests crayg knipser)

set_target_properties(crayg-integration-tests
        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
        LINK_FLAGS "--coverage")