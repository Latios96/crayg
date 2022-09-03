set(UNIT_TEST_LIST
        fixtures/TemporaryDirectory.cpp
        fixtures/TemporaryDirectory.h
        fixtures/TriangleMeshFixtures.cpp
        fixtures/TriangleMeshFixtures.h
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
        TestBvhBuilder.cpp
        TestBvhSceneIntersector.cpp
        TestCamera.cpp
        TestColor.cpp
        TestDebugIntegrator.cpp
        TestDiskLight.cpp
        TestGroundPlane.cpp
        TestImage.cpp
        TestImageAlgorithms.cpp
        TestImageBucketIterator.cpp
        TestImageIterators.cpp
        TestImageOutputDriver.cpp
        TestImagePathResolver.cpp
        TestImageWriters.cpp
        TestIntegratorContext.cpp
        TestIntegratorSettings.cpp
        TestLight.cpp
        TestLineByLineIterator.cpp
        TestMatrix4x4f.cpp
        TestNode.cpp
        TestOpenImageIoImageWriter.cpp
        TestOrthonormalBasis.cpp
        TestPreconditions.cpp
        TestProgressReporter.cpp
        TestRay.cpp
        TestRaytracingIntegrator.cpp
        TestReadableFormatter.cpp
        TestRectLight.cpp
        TestRemainingTimeCalculator.cpp
        TestResolution.cpp
        TestSampleAccumulator.cpp
        TestScene.cpp
        TestSceneIntersector.cpp
        TestSceneReaderFactory.cpp
        TestSceneWriterFactory.cpp
        TestSphere.cpp
        TestSurfaceInteraction.cpp
        TestTeeOutputDriver.cpp
        TestToStringHelper.cpp
        TestTransform.cpp
        TestTriangle.cpp
        TestTriangleMesh.cpp
        TestTriangleMeshConversion.cpp
        TestTriangleMeshPerPointPrimVar.cpp
        TestTriangleMeshPerVertexPrimVar.cpp
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
        TestVector3f.cpp
        )

foreach (NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST ${NAME})
endforeach ()

set(TARGET_NAME crayg-unit-tests)

add_executable(${TARGET_NAME}
        main.cpp
        ${UNIT_TEST_SOURCE_LIST})

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