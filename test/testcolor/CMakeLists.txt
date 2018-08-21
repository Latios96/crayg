file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testcolor ${SRCS})

TARGET_LINK_LIBRARIES(testcolor
    crayg
    libgtest
    libgmock
)

add_test(NAME testcolor
         COMMAND testcolor)
