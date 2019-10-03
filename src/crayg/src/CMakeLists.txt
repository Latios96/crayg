set(crayg_SRCS
        foundation/Vector3f.h
        foundation/Vector3f.cpp
        image/Image.h
        image/Image.cpp
        image/BmpImageWriter.h
        image/BmpImageWriter.cpp
        scene/Camera.h
        scene/Camera.cpp
        PineHoleCameraModel.h
        PineHoleCameraModel.cpp
        foundation/Ray.h
        foundation/Ray.cpp
        intersectors/Intersectable.h
        scene/Sphere.h
        scene/Sphere.cpp
        foundation/Color.h
        foundation/Color.cpp
        scene/Transformable.h
        scene/Transformable.cpp
        scene/Scene.h
        scene/Scene.cpp
        intersectors/Intersector.h
        image/ImageWriter.h
        image/ImageWriterFactory.h
        scene/SceneCreator.h
        image/LineByLineIterator.h
        image/ImageIterators.h
        image/ImageWriters.h
        image/ImageWriters.cpp
        image/OpenImageIoImageWriter.h
        image/OpenImageIoImageWriter.cpp
        utils/ToStringHelper.h
        sceneIO/write/SceneWriter.h
        sceneIO/Serializable.h
        sceneIO/write/json/JsonSerializer.cpp
        sceneIO/write/json/JsonSerializer.h
        sceneIO/read/json/JsonDeserializer.cpp
        sceneIO/read/json/JsonDeserializer.h
        sceneIO/read/SceneReader.cpp
        sceneIO/read/SceneReader.h
        utils/StopWatch.h
        intersectors/SceneIntersector.cpp
        intersectors/SceneIntersector.h
        sceneIO/write/SceneWriter.cpp
        sceneIO/write/SerializerImplementation.h
        Renderer.cpp
        Renderer.h
        utils/utils.h
        scene/Light.h
        scene/Light.cpp
        scene/SceneObject.cpp
        scene/SceneObject.h
        scene/GroundPlane.cpp
        scene/GroundPlane.h
        CameraModel.h
        utils/ProgressReporter.cpp
        utils/ProgressReporter.h
        ShadingMethod.cpp
        ShadingMethod.h
        scene/Triangle.cpp
        scene/Triangle.h
        scene/TriangleMesh.cpp
        scene/TriangleMesh.h
        sceneIO/SceneWriterFactory.cpp
        sceneIO/SceneWriterFactory.h
        sceneIO/write/Serializer.h
        sceneIO/read/Deserializer.h
        sceneIO/SceneReaderFactory.cpp
        sceneIO/SceneReaderFactory.h
        sceneIO/read/json/JsonSceneReader.cpp
        sceneIO/read/json/JsonSceneReader.h
        scene/Imageable.cpp
        scene/Imageable.h
        foundation/BoundingBox.h
        foundation/BoundingBox.cpp
        utils/RemainingTimeCalculator.h
        utils/RemainingTimeCalculator.cpp
        lightSamplers/LightSampler.h
        lightSamplers/LightSampler.cpp
        lightSamplers/PointLightSampler.h
        lightSamplers/PointLightSampler.cpp
        lightSamplers/LightSamplerFactory.h
        Logger.h
        Logger.cpp)


add_library(crayg STATIC
        ${crayg_SRCS})

target_include_directories(crayg PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

# todo link flags only when doing debug build
#set_target_properties(crayg
#        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
#        LINK_FLAGS "--coverage")

target_link_libraries(crayg ${CONAN_LIBS} dl)