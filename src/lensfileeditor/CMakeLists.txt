set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(
    Qt5
    COMPONENTS Core Widgets
    REQUIRED CONFIG)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(
    lensfileeditor-library model/CameraLensModel.cpp model/CameraLensModel.h widgets/CameraLensEditor.cpp
                           widgets/CameraLensEditor.h widgets/LensEditorMainWindow.cpp widgets/LensEditorMainWindow.h)

target_include_directories(lensfileeditor-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lensfileeditor-library crayg qtcrayg Qt5::Core Qt5::Widgets ${CONAN_LIBS})

add_executable(lensfileeditor main.cpp)

target_link_libraries(
    lensfileeditor
    crayg
    lensfileeditor-library
    crayg-standalone-lib
    qtcrayg
    Qt5::Widgets
    Qt5::Core
    ${CONAN_LIBS})
