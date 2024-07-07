set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(
    Qt5
    COMPONENTS Core Widgets
    REQUIRED CONFIG)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(
    crayg-framebuffer
    QtBase.h
    resources/resources.qrc
    resources/StyleSheetLoader.cpp
    resources/StyleSheetLoader.h
    widgets/FrameBufferWidget.cpp
    widgets/FrameBufferWidget.h
    widgets/GuiTaskReporter.cpp
    widgets/GuiTaskReporter.h
    widgets/IconToggleButton.cpp
    widgets/IconToggleButton.h
    widgets/IdConstants.h
    widgets/ImageWidget.cpp
    widgets/ImageWidget.h
    widgets/ImageWidgetOutputDriver.cpp
    widgets/ImageWidgetOutputDriver.h
    widgets/PanAndZoomArea.cpp
    widgets/PanAndZoomArea.h
    widgets/QtMetaTypes.h
    widgets/QtUtils.cpp
    widgets/QtUtils.h
    widgets/QtWidgetsBuilderDsl.cpp
    widgets/QtWidgetsBuilderDsl.h)

target_include_directories(crayg-framebuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(crayg-framebuffer crayg Qt5::Core Qt5::Widgets ${CONAN_LIBS})

if(APPLE)
    set(MAC_OS_ICON_PATH ${CMAKE_SOURCE_DIR}/logo/generated/Logo_black_white.icns)
    set(MACOSX_BUNDLE_ICON_FILE ${MAC_OS_ICON_PATH})

    set(craygStandalone_ICON ${MAC_OS_ICON_PATH})
    set_source_files_properties(${craygStandalone_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(crayg-standalone-gui MACOSX_BUNDLE ${craygStandalone_ICON} main.cpp)
elseif(0)
    set(WINDOWS_APP_ICON_PATH ${CMAKE_SOURCE_DIR}/logo/generated/Logo_white_black.ico)
    configure_file(appicon.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

    add_executable(crayg-standalone-gui WIN32 ${APP_ICON_RESOURCE_WINDOWS} main.cpp)
else()
    add_executable(crayg-standalone-gui main.cpp)
endif()
target_link_libraries(
    crayg-standalone-gui
    crayg
    crayg-framebuffer
    crayg-standalone-lib
    Qt5::Widgets
    Qt5::Core
    ${CONAN_LIBS})

add_custom_command(
    TARGET crayg-standalone-gui
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qt.conf ${CMAKE_BINARY_DIR}/bin/qt.conf)

add_custom_command(
    TARGET crayg-standalone-gui
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONAN_QT_ROOT}/plugins ${CMAKE_BINARY_DIR}/bin/archdatadir/plugins)
