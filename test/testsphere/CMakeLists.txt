file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testsphere ${SRCS})

TARGET_LINK_LIBRARIES(testsphere
    crayg
    libgtest
    libgmock
)

add_test(NAME testsphere
         COMMAND testsphere)
