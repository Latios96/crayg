add_library(crayg_usd STATIC
        Conversions.h
        Conversions.cpp
        CameraTranslator.h
        CameraTranslator.cpp)

target_include_directories(crayg_usd PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(crayg_usd ${CONAN_LIBS} ${CMAKE_DL_LIBS} crayg)