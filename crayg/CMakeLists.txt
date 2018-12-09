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
        scene/TriangeMesh.cpp
        scene/TriangeMesh.h sceneIO/SceneWriterFactory.cpp sceneIO/SceneWriterFactory.h sceneIO/write/Serializer.h sceneIO/read/Deserializer.h sceneIO/SceneReaderFactory.cpp sceneIO/SceneReaderFactory.h sceneIO/read/json/JsonSceneReader.cpp sceneIO/read/json/JsonSceneReader.h scene/Imageable.cpp scene/Imageable.h)

# Declare the library
add_library(crayg STATIC
    ${crayg_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(crayg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(crayg
        PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} --coverage"
        LINK_FLAGS "--coverage")

target_include_directories(crayg
PUBLIC ../externals/rapidjson/ ../externals/fmt/ ../externals/spdlog ../externals/cxxopts)
