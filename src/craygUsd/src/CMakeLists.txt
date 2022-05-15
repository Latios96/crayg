add_library(crayg_usd STATIC
        CraygUsdBase.h
        UsdCameraTranslator.cpp
        UsdCameraTranslator.h
        UsdConversions.cpp
        UsdConversions.h
        UsdMeshTranslator.cpp
        UsdMeshTranslator.h
        UsdSphereLightTranslator.cpp
        UsdSphereLightTranslator.h
        UsdTranslatorUtils.cpp
        UsdTranslatorUtils.h
        UsdUtils.h
        )

target_include_directories(crayg_usd PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(crayg_usd ${CONAN_LIBS} ${CMAKE_DL_LIBS} crayg)

add_custom_command(TARGET crayg_usd PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONAN_LIB_DIRS_USD}/usd ${CMAKE_BINARY_DIR}/bin/usd)