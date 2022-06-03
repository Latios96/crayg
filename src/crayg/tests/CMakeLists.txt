set(UNIT_TEST_LIST
        TestAreaLight.cpp
        TestBaseUsdImageableReader.cpp
        TestBaseUsdLightReader.cpp
        TestBaseUsdReader.cpp
        TestBaseUsdTransformableWriter.cpp
        TestBaseUsdXformableReader.cpp
        TestBmpImageWriter.cpp
        TestBoundingBox.cpp
        TestBucketImageBuffer.cpp
        TestBvhBuilder.cpp
        TestCamera.cpp
        TestColor.cpp
        TestDiskLight.cpp
        TestGroundPlane.cpp
        TestImage.cpp
        TestImageAlgorithms.cpp
        TestImageBucketIterator.cpp
        TestImageIterators.cpp
        TestImageOutputDriver.cpp
        TestImagePathResolver.cpp
        TestImageWriters.cpp
        TestJsonDeserializer.cpp
        TestJsonSceneReader.cpp
        TestJsonSerializer.cpp
        TestLight.cpp
        TestLineByLineIterator.cpp
        TestMatrix4x4f.cpp
        TestNode.cpp
        TestOpenImageIoImageWriter.cpp
        TestPointCloud.cpp
        TestPreconditions.cpp
        TestProgressReporter.cpp
        TestRay.cpp
        TestReadableFormatter.cpp
        TestRectLight.cpp
        TestRemainingTimeCalculator.cpp
        TestResolution.cpp
        TestScene.cpp
        TestSceneIntersector.cpp
        TestSceneObject.cpp
        TestSceneReaderFactory.cpp
        TestShadingMethod.cpp
        TestSphere.cpp
        TestTeeOutputDriver.cpp
        TestToStringHelper.cpp
        TestTransform.cpp
        TestTriangle.cpp
        TestTriangleMesh.cpp
        TestUnitImageSampler.cpp
        TestUsdCameraReader.cpp
        TestUsdConversions.cpp
        TestUsdDiskLightReader.cpp
        TestUsdMaterialReadCache.cpp
        TestUsdMeshReader.cpp
        TestUsdPathFactory.cpp
        TestUsdReadUtils.cpp
        TestUsdRectLightReader.cpp
        TestUsdRenderSettingsReader.cpp
        TestUsdRenderSettingsWriter.cpp
        TestUsdSphereLightReader.cpp
        TestUsdSphereReader.cpp
        TestUsdStageReader.cpp
        TestVector.cpp
        )

foreach (NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST ${NAME})
endforeach ()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        main.cpp
        ${UNIT_TEST_SOURCE_LIST} TestBvhBuilder.cpp TestBvhSceneIntersector.cpp)

target_link_libraries(${TARGET_NAME}
        PUBLIC crayg)

if (${BUILD_WITH_COVERAGE})
    set_target_properties(${TARGET_NAME}
            PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
            LINK_FLAGS "--coverage")
endif ()


add_test(
        NAME ${TARGET_NAME}
        COMMAND ${TARGET_NAME} --durations yes)