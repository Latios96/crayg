

configure_file(${CMAKE_BINARY_DIR}/qt.conf ${CMAKE_BINARY_DIR}/bin/qt.conf COPYONLY)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


add_library(crayg-framebuffer FrameBufferWidget.h
        FrameBufferWidget.cpp)
target_include_directories(crayg-framebuffer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(crayg-framebuffer Qt5::Core Qt5::Widgets ${CONAN_LIBS})


add_executable(standalone-gui
        main.cpp
        FrameBufferWidget.h
        FrameBufferWidget.cpp)
target_link_libraries(standalone-gui crayg-framebuffer Qt5::Core Qt5::Widgets ${CONAN_LIBS})
