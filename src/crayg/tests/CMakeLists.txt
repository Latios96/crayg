
set(UNIT_TEST_LIST
        TestColor.cpp
        TestImage.cpp
        TestSphere.cpp
        TestVector.cpp
        TestToStringHelper.cpp
        TestLineByLineIterator.cpp
        TestBmpImageWriter.cpp
        TestSceneIntersector.cpp
        TestSceneWriter.cpp
        TestRay.cpp
        TestLight.cpp
        TestProgressReporter.cpp
        TestShadingMethod.cpp
        TestTriangle.cpp
        TestTriangleMesh.cpp
        TestRemainingTimeCalculator.cpp
        TestGroundPlane.cpp
        TestCamera.cpp
        TestJsonDeserializer.cpp
        TestJsonSceneReader.cpp
        TestBoundingBox.cpp
        TestPointLightSampler.cpp
        TestImageWriters.cpp
        TestOpenImageIoImageWriter.cpp
        TestUnitImageSampler.cpp
        TestPointCloud.cpp
        TestImageBucketIterator.cpp
        TestImageIterators.cpp
        TestBucketImageBuffer.cpp
        TestImageAlgorithms.cpp
        TestImageOutputDriver.cpp
        )

foreach (NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST ${NAME})
endforeach ()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        main.cpp
        ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
        PUBLIC crayg)

target_include_directories(${TARGET_NAME}
        PUBLIC ../../externals/fakeIt)

if (${BUILD_WITH_COVERAGE})
    set_target_properties(${TARGET_NAME}
            PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
            LINK_FLAGS "--coverage")
endif ()


add_test(
        NAME ${TARGET_NAME}
        COMMAND ${TARGET_NAME} --durations yes)