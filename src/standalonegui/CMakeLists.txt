find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


add_library(crayg-framebuffer
        FrameBufferWidget.h
        FrameBufferWidget.cpp
        ImageWidget.h
        ImageWidget.cpp
        ImageWidgetOutputDriver.h
        ImageWidgetOutputDriver.cpp
        )
target_include_directories(crayg-framebuffer PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(crayg-framebuffer crayg Qt5::Core Qt5::Widgets ${CONAN_LIBS})


add_executable(standalone-gui
        main.cpp)
target_link_libraries(standalone-gui crayg crayg-framebuffer crayg-standalone-lib Qt5::Core Qt5::Widgets ${CONAN_LIBS})

add_custom_command(TARGET standalone-gui PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONAN_QT_ROOT}/plugins ${CMAKE_BINARY_DIR}/bin/plugins)