set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
find_package(
    Qt5
    COMPONENTS Core Widgets
    REQUIRED CONFIG)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(
    qtcrayg
    qtcrayg/foundation/QtBase.h
    qtcrayg/foundation/QtMetaTypes.h
    qtcrayg/resources/resources.qrc
    qtcrayg/resources/StyleSheetLoader.cpp
    qtcrayg/resources/StyleSheetLoader.h
    qtcrayg/utils/QtUtils.cpp
    qtcrayg/utils/QtUtils.h
    qtcrayg/widgets/IconToggleButton.cpp
    qtcrayg/widgets/IconToggleButton.h
    qtcrayg/widgets/QtWidgetsBuilderDsl.cpp
    qtcrayg/widgets/QtWidgetsBuilderDsl.h)

target_include_directories(qtcrayg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(qtcrayg crayg Qt5::Core Qt5::Widgets ${CONAN_LIBS})

add_custom_command(
    TARGET qtcrayg
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/qt.conf ${CMAKE_BINARY_DIR}/bin/qt.conf)

add_custom_command(
    TARGET qtcrayg
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONAN_QT_ROOT}/plugins ${CMAKE_BINARY_DIR}/bin/archdatadir/plugins)
