set(crayg_SRCS
    # cmake-format: sortable
    basics/Bound2d.h
    basics/BoundingBox.cpp
    basics/BoundingBox.h
    basics/Color.cpp
    basics/Color.h
    basics/containers/Array2d.h
    basics/Gradient.h
    basics/math/CommonMath.h
    basics/math/QuadraticEquations.h
    basics/Matrix4x4f.cpp
    basics/Matrix4x4f.h
    basics/OrthonormalBasis.cpp
    basics/OrthonormalBasis.h
    basics/Ray.cpp
    basics/Ray.h
    basics/Resolution.cpp
    basics/Resolution.h
    basics/Transform.cpp
    basics/Transform.h
    basics/Vector2.h
    basics/Vector3f.cpp
    basics/Vector3f.h
    CraygInfo.cpp
    CraygInfo.h
    image/BucketImageBuffer.cpp
    image/BucketImageBuffer.h
    image/ColorConversion.cpp
    image/ColorConversion.h
    image/film/buffers/FilmAccumulationBuffer.h
    image/film/buffers/FilmBufferBase.h
    image/film/buffers/FilmBufferFactory.cpp
    image/film/buffers/FilmBufferFactory.h
    image/film/buffers/FilmBufferType.h
    image/film/buffers/FilmBufferVariants.cpp
    image/film/buffers/FilmBufferVariants.h
    image/film/buffers/FilmSumBuffer.h
    image/film/buffers/FilmValueBuffer.h
    image/film/buffers/FilmValueTrait.h
    image/film/Film.cpp
    image/film/Film.h
    image/film/FilmSpec.cpp
    image/film/FilmSpec.h
    image/film/io/FilmWriter.cpp
    image/film/io/FilmWriter.h
    image/Image.cpp
    image/Image.h
    image/ImageAlgorithms.cpp
    image/ImageAlgorithms.h
    image/ImageBucket.cpp
    image/ImageBucket.h
    image/imageiterators/buckets/bucketqueues/BucketQueue.cpp
    image/imageiterators/buckets/bucketqueues/BucketQueue.h
    image/imageiterators/buckets/bucketqueues/BucketQueueMode.h
    image/imageiterators/buckets/bucketqueues/FollowMouseBucketQueue.cpp
    image/imageiterators/buckets/bucketqueues/FollowMouseBucketQueue.h
    image/imageiterators/buckets/bucketqueues/FollowSequenceBucketQueue.cpp
    image/imageiterators/buckets/bucketqueues/FollowSequenceBucketQueue.h
    image/imageiterators/buckets/BucketSequence.h
    image/imageiterators/buckets/BucketSequenceType.h
    image/imageiterators/buckets/HilbertSequence.cpp
    image/imageiterators/buckets/HilbertSequence.h
    image/imageiterators/buckets/ImageBucketSequences.cpp
    image/imageiterators/buckets/ImageBucketSequences.h
    image/imageiterators/buckets/LineByLineSequence.cpp
    image/imageiterators/buckets/LineByLineSequence.h
    image/imageiterators/buckets/MortonSequence.cpp
    image/imageiterators/buckets/MortonSequence.h
    image/imageiterators/buckets/SpiralSequence.cpp
    image/imageiterators/buckets/SpiralSequence.h
    image/imageiterators/pixels/ImageIterators.h
    image/imageiterators/pixels/LineByLineIterator.h
    image/ImageMetadata.cpp
    image/ImageMetadata.h
    image/ImageMetadataValue.h
    image/ImageSpec.cpp
    image/ImageSpec.h
    image/InvalidPixelFormat.h
    image/io/imageformatwriters/exr/OpenExrImageFormatWriter.cpp
    image/io/imageformatwriters/exr/OpenExrImageFormatWriter.h
    image/io/imageformatwriters/ImageBufferTypeTrait.h
    image/io/imageformatwriters/ImageFormatWriter.h
    image/io/imageformatwriters/ImageFormatWriters.cpp
    image/io/imageformatwriters/ImageFormatWriters.h
    image/io/imageformatwriters/png/PngImageFormatWriter.cpp
    image/io/imageformatwriters/png/PngImageFormatWriter.h
    image/io/ImageWriter.h
    image/io/ImageWriters.cpp
    image/io/ImageWriters.h
    image/io/OpenExrWriter.cpp
    image/io/OpenExrWriter.h
    image/io/OpenImageIoImageWriter.cpp
    image/io/OpenImageIoImageWriter.h
    image/io/PngWriter.cpp
    image/io/PngWriter.h
    image/PixelBuffer.cpp
    image/PixelBuffer.h
    image/PixelFormat.h
    Initialization.cpp
    Initialization.cpp
    Initialization.h
    Initialization.h
    integrators/AbstractIntegrator.cpp
    integrators/AbstractIntegrator.h
    integrators/AmbientOcclusionIntegrator.cpp
    integrators/AmbientOcclusionIntegrator.h
    integrators/DebugIntegrator.cpp
    integrators/DebugIntegrator.h
    integrators/IntegratorFactory.cpp
    integrators/IntegratorFactory.h
    integrators/IntegratorSettings.cpp
    integrators/IntegratorSettings.h
    integrators/IntegratorSettingsValue.h
    integrators/IntegratorType.h
    integrators/RaytracingIntegrator.cpp
    integrators/RaytracingIntegrator.h
    integrators/SurfaceInteraction.cpp
    integrators/SurfaceInteraction.h
    intersectors/embree/EmbreeBvh.cpp
    intersectors/embree/EmbreeBvh.h
    intersectors/embree/EmbreeBvhBuilder.cpp
    intersectors/embree/EmbreeBvhBuilder.h
    intersectors/embree/EmbreeSceneIntersector.cpp
    intersectors/embree/EmbreeSceneIntersector.h
    intersectors/embree/EmbreeUtils.cpp
    intersectors/embree/EmbreeUtils.h
    intersectors/IntersectorFactory.cpp
    intersectors/IntersectorFactory.h
    intersectors/IntersectorType.h
    intersectors/SceneIntersector.h
    Logger.cpp
    Logger.h
    outputdrivers/NextGenOutputDriver.cpp
    outputdrivers/NextGenOutputDriver.h
    parallel/ParallelLoops.h
    parallel/ThreadCount.cpp
    parallel/ThreadCount.h
    renderer/bucketsamplers/AdaptiveBucketSampler.cpp
    renderer/bucketsamplers/AdaptiveBucketSampler.h
    renderer/bucketsamplers/BucketSampler.cpp
    renderer/bucketsamplers/BucketSampler.h
    renderer/bucketsamplers/BucketSamplerFactory.cpp
    renderer/bucketsamplers/BucketSamplerFactory.h
    renderer/bucketsamplers/BucketSamplerType.h
    renderer/bucketsamplers/UniformBucketSampler.cpp
    renderer/bucketsamplers/UniformBucketSampler.h
    renderer/BucketSizeEstimator.cpp
    renderer/BucketSizeEstimator.h
    renderer/BucketStats.cpp
    renderer/BucketStats.h
    renderer/FlareRenderer.cpp
    renderer/FlareRenderer.h
    renderer/GeometryCompiler.cpp
    renderer/GeometryCompiler.h
    renderer/Renderer.cpp
    renderer/Renderer.h
    renderer/SampleAccumulator.cpp
    renderer/SampleAccumulator.h
    sampling/Random.cpp
    sampling/Random.h
    sampling/Sampling.cpp
    sampling/Sampling.h
    sampling/UnitSphereSampler.cpp
    sampling/UnitSphereSampler.h
    scene/camera/Camera.cpp
    scene/camera/Camera.h
    scene/camera/CameraModel.h
    scene/camera/CameraModelFactory.cpp
    scene/camera/CameraModelFactory.h
    scene/camera/CameraType.h
    scene/camera/CameraUtils.cpp
    scene/camera/CameraUtils.h
    scene/camera/pinhole/PinholeCameraModel.cpp
    scene/camera/pinhole/PinholeCameraModel.h
    scene/camera/realistic/CameraLens.cpp
    scene/camera/realistic/CameraLens.h
    scene/camera/realistic/CameraLensMetadata.cpp
    scene/camera/realistic/CameraLensMetadata.h
    scene/camera/realistic/ExitPupil.cpp
    scene/camera/realistic/ExitPupil.h
    scene/camera/realistic/ExitPupilCalculator.cpp
    scene/camera/realistic/ExitPupilCalculator.h
    scene/camera/realistic/LensGeometry.h
    scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatReader.cpp
    scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatReader.h
    scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatWriter.cpp
    scene/camera/realistic/lensio/extendedformat/LensFileExtendedFormatWriter.h
    scene/camera/realistic/lensio/json/LensFileJsonReader.cpp
    scene/camera/realistic/lensio/json/LensFileJsonReader.h
    scene/camera/realistic/lensio/json/LensFileJsonWriter.cpp
    scene/camera/realistic/lensio/json/LensFileJsonWriter.h
    scene/camera/realistic/lensio/LensFileFormat.h
    scene/camera/realistic/lensio/LensFileParseUtils.cpp
    scene/camera/realistic/lensio/LensFileParseUtils.h
    scene/camera/realistic/lensio/LensFileReader.cpp
    scene/camera/realistic/lensio/LensFileReader.h
    scene/camera/realistic/lensio/LensFileReaderFactory.cpp
    scene/camera/realistic/lensio/LensFileReaderFactory.h
    scene/camera/realistic/lensio/LensFileWriter.cpp
    scene/camera/realistic/lensio/LensFileWriter.h
    scene/camera/realistic/lensio/LensFileWriterFactory.cpp
    scene/camera/realistic/lensio/LensFileWriterFactory.h
    scene/camera/realistic/lensio/textfile/LensFileTextFileReader.cpp
    scene/camera/realistic/lensio/textfile/LensFileTextFileReader.h
    scene/camera/realistic/lensio/textfile/LensFileTextFileWriter.cpp
    scene/camera/realistic/lensio/textfile/LensFileTextFileWriter.h
    scene/camera/realistic/lensio/zmx/ZMXFileFormatReader.cpp
    scene/camera/realistic/lensio/zmx/ZMXFileFormatReader.h
    scene/camera/realistic/LensMaterial.cpp
    scene/camera/realistic/LensMaterial.h
    scene/camera/realistic/LensRaytracerTracer.cpp
    scene/camera/realistic/LensRaytracerTracer.h
    scene/camera/realistic/LensSurface.cpp
    scene/camera/realistic/LensSurface.h
    scene/camera/realistic/materials/LensMaterialConstants_ohara.h
    scene/camera/realistic/materials/LensMaterialConstants_schott.h
    scene/camera/realistic/materials/LensMaterialIds_ohara.h
    scene/camera/realistic/materials/LensMaterialIds_schott.h
    scene/camera/realistic/RealisticCameraModel.cpp
    scene/camera/realistic/RealisticCameraModel.h
    scene/camera/realistic/ThickLensApproximation.cpp
    scene/camera/realistic/ThickLensApproximation.h
    scene/camera/realistic/VariableLensDistances.cpp
    scene/camera/realistic/VariableLensDistances.h
    scene/camera/realistic/Wavelengths.cpp
    scene/camera/realistic/Wavelengths.h
    scene/camera/thinlens/ThinLensCameraModel.cpp
    scene/camera/thinlens/ThinLensCameraModel.h
    scene/Imageable.cpp
    scene/Imageable.h
    scene/lights/AreaLight.cpp
    scene/lights/AreaLight.h
    scene/lights/DiskLight.cpp
    scene/lights/DiskLight.h
    scene/lights/Light.cpp
    scene/lights/Light.h
    scene/lights/RectLight.cpp
    scene/lights/RectLight.h
    scene/lights/shapegenerators/AbstractLightShapeGenerator.cpp
    scene/lights/shapegenerators/AbstractLightShapeGenerator.h
    scene/lights/shapegenerators/DiskLightShapeGenerator.cpp
    scene/lights/shapegenerators/DiskLightShapeGenerator.h
    scene/lights/shapegenerators/RectLightShapeGenerator.cpp
    scene/lights/shapegenerators/RectLightShapeGenerator.h
    scene/primitives/GroundPlane.cpp
    scene/primitives/GroundPlane.h
    scene/primitives/PointInstancer.cpp
    scene/primitives/PointInstancer.h
    scene/primitives/Sphere.cpp
    scene/primitives/Sphere.h
    scene/primitives/subdivisionsurfacemesh/FanTriangulator.cpp
    scene/primitives/subdivisionsurfacemesh/FanTriangulator.h
    scene/primitives/subdivisionsurfacemesh/OpenSubdivRefiner.cpp
    scene/primitives/subdivisionsurfacemesh/OpenSubdivRefiner.h
    scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.cpp
    scene/primitives/subdivisionsurfacemesh/SubdivisionSurfaceMesh.h
    scene/primitives/trianglemesh/BarycentricCoordinates.cpp
    scene/primitives/trianglemesh/BarycentricCoordinates.h
    scene/primitives/trianglemesh/primvars/PrimVarType.h
    scene/primitives/trianglemesh/primvars/TriangleMeshAbstractPrimVar.h
    scene/primitives/trianglemesh/primvars/TriangleMeshPerFacePrimVar.h
    scene/primitives/trianglemesh/primvars/TriangleMeshPerPointPrimVar.h
    scene/primitives/trianglemesh/primvars/TriangleMeshPerVertexPrimVar.h
    scene/primitives/trianglemesh/Triangle.cpp
    scene/primitives/trianglemesh/Triangle.h
    scene/primitives/trianglemesh/TriangleMesh.cpp
    scene/primitives/trianglemesh/TriangleMesh.h
    scene/primitives/trianglemesh/TriangleMeshConversion.cpp
    scene/primitives/trianglemesh/TriangleMeshConversion.h
    scene/RegionToRender.cpp
    scene/RegionToRender.h
    scene/RenderSettings.cpp
    scene/RenderSettings.h
    scene/Scene.cpp
    scene/Scene.h
    scene/SceneObject.cpp
    scene/SceneObject.h
    scene/shadingnetworks/materials/EmissiveMaterial.cpp
    scene/shadingnetworks/materials/EmissiveMaterial.h
    scene/shadingnetworks/materials/Material.cpp
    scene/shadingnetworks/materials/Material.h
    scene/shadingnetworks/materials/UsdPreviewSurface.cpp
    scene/shadingnetworks/materials/UsdPreviewSurface.h
    scene/shadingnetworks/ShadingNode.cpp
    scene/shadingnetworks/ShadingNode.h
    scene/shadingnetworks/shadingnodes/CheckerBoard.cpp
    scene/shadingnetworks/shadingnodes/CheckerBoard.h
    scene/shadingnetworks/shadingnodes/ColorToFloat.cpp
    scene/shadingnetworks/shadingnodes/ColorToFloat.h
    scene/shadingnetworks/shadingnodes/ConstantShadingNodes.cpp
    scene/shadingnetworks/shadingnodes/ConstantShadingNodes.h
    scene/shadingnetworks/shadingnodes/ConversionNodes.cpp
    scene/shadingnetworks/shadingnodes/ConversionNodes.h
    scene/shadingnetworks/shadingnodes/FileTexture.cpp
    scene/shadingnetworks/shadingnodes/FileTexture.h
    scene/shadingnetworks/shadingnodes/PrimVarReaders.cpp
    scene/shadingnetworks/shadingnodes/PrimVarReaders.h
    scene/Transformable.cpp
    scene/Transformable.h
    sceneIO/read/SceneReader.cpp
    sceneIO/read/SceneReader.h
    sceneIO/read/usd/base/BaseUsdImageableReader.h
    sceneIO/read/usd/base/BaseUsdLightReader.h
    sceneIO/read/usd/base/BaseUsdReader.h
    sceneIO/read/usd/base/BaseUsdShadingNodeReader.cpp
    sceneIO/read/usd/base/BaseUsdShadingNodeReader.h
    sceneIO/read/usd/base/BaseUsdXformableReader.h
    sceneIO/read/usd/camera/UsdCameraReader.cpp
    sceneIO/read/usd/camera/UsdCameraReader.h
    sceneIO/read/usd/lights/UsdDiskLightReader.cpp
    sceneIO/read/usd/lights/UsdDiskLightReader.h
    sceneIO/read/usd/lights/UsdRectLightReader.cpp
    sceneIO/read/usd/lights/UsdRectLightReader.h
    sceneIO/read/usd/lights/UsdSphereLightReader.cpp
    sceneIO/read/usd/lights/UsdSphereLightReader.h
    sceneIO/read/usd/primitives/UsdMeshReader.cpp
    sceneIO/read/usd/primitives/UsdMeshReader.h
    sceneIO/read/usd/primitives/UsdPointInstancerReader.cpp
    sceneIO/read/usd/primitives/UsdPointInstancerReader.h
    sceneIO/read/usd/primitives/UsdSphereReader.cpp
    sceneIO/read/usd/primitives/UsdSphereReader.h
    sceneIO/read/usd/primitives/UsdSubdivisionSurfaceMeshReader.cpp
    sceneIO/read/usd/primitives/UsdSubdivisionSurfaceMeshReader.h
    sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.cpp
    sceneIO/read/usd/shadingnetworks/caches/UsdMaterialReadCache.h
    sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.cpp
    sceneIO/read/usd/shadingnetworks/caches/UsdShadingNodeReadCache.h
    sceneIO/read/usd/shadingnetworks/materials/UsdPreviewSurfaceReader.cpp
    sceneIO/read/usd/shadingnetworks/materials/UsdPreviewSurfaceReader.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdCheckerBoardReader.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdCheckerBoardReader.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdColorToFloatReader.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdColorToFloatReader.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeReaders.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeReaders.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdConversionNodesReaders.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdFileTextureReader.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdFileTextureReader.h
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderReaders.cpp
    sceneIO/read/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderReaders.h
    sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.cpp
    sceneIO/read/usd/shadingnetworks/UsdShadingNodeReadUtils.h
    sceneIO/read/usd/UsdRenderSettingsReader.cpp
    sceneIO/read/usd/UsdRenderSettingsReader.h
    sceneIO/read/usd/UsdSceneReader.cpp
    sceneIO/read/usd/UsdSceneReader.h
    sceneIO/read/usd/UsdStageReader.cpp
    sceneIO/read/usd/UsdStageReader.h
    sceneIO/SceneReaderFactory.cpp
    sceneIO/SceneReaderFactory.h
    sceneIO/SceneWriterFactory.cpp
    sceneIO/SceneWriterFactory.h
    sceneIO/usd/CraygUsdBase.h
    sceneIO/usd/UsdConversions.cpp
    sceneIO/usd/UsdConversions.h
    sceneIO/usd/UsdLensFileUtils.cpp
    sceneIO/usd/UsdLensFileUtils.h
    sceneIO/usd/UsdReadUtils.cpp
    sceneIO/usd/UsdReadUtils.h
    sceneIO/usd/UsdTypeUtil.h
    sceneIO/usd/UsdUtils.h
    sceneIO/write/SceneWriter.cpp
    sceneIO/write/SceneWriter.h
    sceneIO/write/usd/base/BaseUsdLightWriter.h
    sceneIO/write/usd/base/BaseUsdMaterialWriter.h
    sceneIO/write/usd/base/BaseUsdSceneObjectWriter.h
    sceneIO/write/usd/base/BaseUsdShadingNodeWriter.h
    sceneIO/write/usd/base/BaseUsdTransformableWriter.h
    sceneIO/write/usd/base/BaseUsdWriter.h
    sceneIO/write/usd/camera/UsdCameraWriter.cpp
    sceneIO/write/usd/camera/UsdCameraWriter.h
    sceneIO/write/usd/lights/UsdDiskLightWriter.cpp
    sceneIO/write/usd/lights/UsdDiskLightWriter.h
    sceneIO/write/usd/lights/UsdPointLightWriter.cpp
    sceneIO/write/usd/lights/UsdPointLightWriter.h
    sceneIO/write/usd/lights/UsdRectLightWriter.cpp
    sceneIO/write/usd/lights/UsdRectLightWriter.h
    sceneIO/write/usd/primitives/UsdGroundPlaneWriter.cpp
    sceneIO/write/usd/primitives/UsdGroundPlaneWriter.h
    sceneIO/write/usd/primitives/UsdPointInstancerWriter.cpp
    sceneIO/write/usd/primitives/UsdPointInstancerWriter.h
    sceneIO/write/usd/primitives/UsdSphereWriter.cpp
    sceneIO/write/usd/primitives/UsdSphereWriter.h
    sceneIO/write/usd/primitives/UsdSubdivisionSurfaceMeshWriter.cpp
    sceneIO/write/usd/primitives/UsdSubdivisionSurfaceMeshWriter.h
    sceneIO/write/usd/primitives/UsdTriangleMeshWriter.cpp
    sceneIO/write/usd/primitives/UsdTriangleMeshWriter.h
    sceneIO/write/usd/shadingnetworks/caches/UsdMaterialWriteCache.cpp
    sceneIO/write/usd/shadingnetworks/caches/UsdMaterialWriteCache.h
    sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.cpp
    sceneIO/write/usd/shadingnetworks/caches/UsdShadingNodeWriteCache.h
    sceneIO/write/usd/shadingnetworks/materials/UsdPreviewSurfaceWriter.cpp
    sceneIO/write/usd/shadingnetworks/materials/UsdPreviewSurfaceWriter.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdCheckerBoardWriter.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdCheckerBoardWriter.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdColorToFloatWriter.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdColorToFloatWriter.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeWriters.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConstantShadingNodeWriters.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConversionNodeWriters.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdConversionNodeWriters.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdFileTextureWriter.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdFileTextureWriter.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdFileTextureWriter.h
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderWriters.cpp
    sceneIO/write/usd/shadingnetworks/shadingnodes/UsdPrimVarReaderWriters.cpp
    sceneIO/write/usd/UsdPathFactory.cpp
    sceneIO/write/usd/UsdPathFactory.h
    sceneIO/write/usd/UsdRenderSettingsWriter.cpp
    sceneIO/write/usd/UsdRenderSettingsWriter.h
    sceneIO/write/usd/UsdSceneWriter.cpp
    sceneIO/write/usd/UsdSceneWriter.h
    utils/AtomicFloats.h
    utils/BitCast.h
    utils/CraygMain.h
    utils/DtoUtils.h
    utils/EnumFormatter.h
    utils/EnumParser.h
    utils/Exceptions.cpp
    utils/Exceptions.h
    utils/FileSystemUtils.cpp
    utils/FileSystemUtils.h
    utils/Heatmap.cpp
    utils/Heatmap.h
    utils/ImageChannelPathResolver.cpp
    utils/ImageChannelPathResolver.h
    utils/ImageMetadataCollector.cpp
    utils/ImageMetadataCollector.h
    utils/ImagePathResolver.cpp
    utils/ImagePathResolver.h
    utils/NumberParsing.cpp
    utils/NumberParsing.h
    utils/Preconditions.h
    utils/ProgressReporter.cpp
    utils/ProgressReporter.h
    utils/ReadableFormatter.cpp
    utils/ReadableFormatter.h
    utils/RemainingTimeCalculator.cpp
    utils/RemainingTimeCalculator.h
    utils/StopWatch.cpp
    utils/StopWatch.h
    utils/TaskReporter.cpp
    utils/TaskReporter.h
    utils/TextureStats.cpp
    utils/TextureStats.h
    utils/ToStringHelper.h
    utils/tracing/CraygTracing.h
    utils/utils.cpp
    utils/utils.h
    utils/ValueMapper.h)

add_library(crayg STATIC ${crayg_SRCS})

target_include_directories(crayg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_compile_definitions(crayg PUBLIC NOMINMAX _USE_MATH_DEFINES)
endif()
target_compile_definitions(crayg PUBLIC MAGIC_ENUM_RANGE_MAX=256 CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS=1
                                        TBB_PREVIEW_CONCURRENT_ORDERED_CONTAINERS=1)

add_custom_command(
    TARGET crayg
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONAN_LIB_DIRS_USD}/usd ${CMAKE_BINARY_DIR}/bin/usd)

target_link_libraries(
    crayg
    ${CONAN_LIBS}
    ${CMAKE_DL_LIBS}
    cpptrace
    gilbert
    minitrace
    text_encoding_detect)
