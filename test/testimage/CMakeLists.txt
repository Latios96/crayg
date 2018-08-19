file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testimage ${SRCS})

TARGET_LINK_LIBRARIES(testimage
    crayg
    libgtest
    libgmock
)

add_test(NAME testimage
         COMMAND testimage)
