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
        sceneIO/SceneWriter.h
        sceneIO/Serializable.h
        sceneIO/JsonSerializer.cpp
        sceneIO/JsonSerializer.h
        sceneIO/JsonDeserializer.cpp
        sceneIO/JsonDeserializer.h
        sceneIO/SceneReader.cpp
        sceneIO/SceneReader.h
        utils/StopWatch.h
        intersectors/SceneIntersector.cpp
        intersectors/SceneIntersector.h sceneIO/SceneWriter.cpp sceneIO/SerializerImplementation.h Renderer.cpp Renderer.h utils/utils.h scene/Light.h scene/Light.cpp)

# Declare the library
add_library(crayg STATIC
    ${crayg_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(crayg PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(crayg
PUBLIC ../externals/rapidjson/ ../externals/fmt/ ../externals/spdlog ../externals/cxxopts)
