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

install(TARGETS crayg-standalone DESTINATION bin)
