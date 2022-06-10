set(UNIT_TEST_LIST
        TestAreaLight.cpp
        TestBarycentricCoordinates.cpp
        TestBaseUsdImageableReader.cpp
        TestBaseUsdLightReader.cpp
        TestBaseUsdLightWriter.cpp
        TestBaseUsdReader.cpp
        TestBaseUsdSceneObjectWriter.cpp
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
        TestLight.cpp
        TestLineByLineIterator.cpp
        TestMatrix4x4f.cpp
        TestNode.cpp
        TestOpenImageIoImageWriter.cpp
        TestPreconditions.cpp
        TestProgressReporter.cpp
        TestRay.cpp
        TestReadableFormatter.cpp
        TestRectLight.cpp
        TestRemainingTimeCalculator.cpp
        TestResolution.cpp
        TestScene.cpp
        TestSceneIntersector.cpp
        TestSceneReaderFactory.cpp
        TestSceneWriterFactory.cpp
        TestShadingMethod.cpp
        TestSphere.cpp
        TestTeeOutputDriver.cpp
        TestToStringHelper.cpp
        TestTransform.cpp
        TestTriangle.cpp
        TestTriangleMesh.cpp
        TestTriangleMeshConversion.cpp
        TestUnitImageSampler.cpp
        TestUsdCameraReader.cpp
        TestUsdCameraWriter.cpp
        TestUsdConversions.cpp
        TestUsdDiskLightReader.cpp
        TestUsdDiskLightWriter.cpp
        TestUsdGroundPlaneWriter.cpp
        TestUsdMaterialReadCache.cpp
        TestUsdMaterialWriteCache.cpp
        TestUsdMeshReader.cpp
        TestUsdPathFactory.cpp
        TestUsdPointLightWriter.cpp
        TestUsdReadUtils.cpp
        TestUsdRectLightReader.cpp
        TestUsdRectLightWriter.cpp
        TestUsdRenderSettingsReader.cpp
        TestUsdRenderSettingsWriter.cpp
        TestUsdSceneWriter.cpp
        TestUsdSphereLightReader.cpp
        TestUsdSphereReader.cpp
        TestUsdSphereWriter.cpp
        TestUsdStageReader.cpp
        TestUsdTriangleMeshWriter.cpp
        TestUsdUtils.cpp
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