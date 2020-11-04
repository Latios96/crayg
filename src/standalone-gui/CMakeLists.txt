

configure_file(${CMAKE_BINARY_DIR}/qt.conf ${CMAKE_BINARY_DIR}/bin COPYONLY)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(standalone_gui
        main.cpp
        FrameBufferWidget.h
        FrameBufferWidget.cpp)

target_link_libraries(standalone_gui Qt5::Core Qt5::Widgets ${CONAN_LIBS})