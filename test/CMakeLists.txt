
set(UNIT_TEST_LIST
        testcolor.cpp
        testimage.cpp
        testsphere.cpp
        testvector.cpp
        testToStringHelper.cpp
        testLineByLineIterator.cpp
        )

foreach(NAME IN LISTS UNIT_TEST_LIST)
  list(APPEND UNIT_TEST_SOURCE_LIST ${NAME})
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST} testbmpimagewriter.cpp testsceneintersector.cpp testscenewriter.cpp testray.cpp testlight.cpp testprogressreporter.cpp testshadingmethod.cpp testtriangle.cpp testtrianglemesh.cpp)

target_link_libraries(${TARGET_NAME}
  PUBLIC crayg)

target_include_directories(${TARGET_NAME}
  PUBLIC ../externals/catch2/ ../externals/fakeIt)

set_target_properties(${TARGET_NAME}
        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
                LINK_FLAGS "--coverage")

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit)