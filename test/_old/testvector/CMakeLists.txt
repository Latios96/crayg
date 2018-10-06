file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testvector ${SRCS})

TARGET_LINK_LIBRARIES(testvector
    crayg
    libgtest
    libgmock
)

add_test(NAME testvector
         COMMAND testvector)
