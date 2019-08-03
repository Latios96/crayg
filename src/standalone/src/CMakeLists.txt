set(Main_SRCS
        main.cpp
)

add_executable(crayg-standalone
    ${Main_SRCS}
)

# Specify here the libraries this program depends on
target_link_libraries(crayg-standalone
    crayg
)

set_target_properties(crayg-standalone
        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
        LINK_FLAGS "--coverage")


install(TARGETS crayg-standalone DESTINATION bin)
