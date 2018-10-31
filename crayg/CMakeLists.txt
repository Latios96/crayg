set(crayg_SRCS
        foundation/Vector3f.h
        foundation/Vector3f.cpp
        image/Image.h
        image/Image.cpp
        image/BmpImageWriter.h
        image/BmpImageWriter.cpp
        Camera.h
        Camera.cpp
        PineHoleCameraModel.h
        PineHoleCameraModel.cpp
        foundation/Ray.h
        foundation/Ray.cpp
        Intersectable.h
        Sphere.h
        Sphere.cpp
        foundation/Color.h
        foundation/Color.cpp
        Transformable.h
        Transformable.cpp
        Scene.h
        Scene.cpp
        prims/Stage.cpp
        prims/Stage.h
        prims/Prim.cpp
        prims/Prim.h
        prims/Attribute.cpp
        prims/Attribute.h
        prims/AttributeImpl.cpp
        prims/AttributeImpl.h
        schemas/SpherePrim.cpp
        schemas/SpherePrim.h
        schemas/ImageablePrim.h
        schemas/TransformablePrim.cpp
        schemas/TransformablePrim.h
        schemas/ImageablePrim.cpp
        intersectors/Intersector.h
        intersectors/SphereIntersector.cpp
        intersectors/SphereIntersector.h
        image/ImageWriter.h
        image/ImageWriterFactory.h
        SceneCreator.h
        image/LineByLineIterator.h
        image/ImageIterators.h
        utils/ToStringHelper.h
        sceneIO/SceneWriter.cpp
        sceneIO/SceneWriter.h
        sceneIO/Serializable.h
        sceneIO/JsonSerializer.cpp
        sceneIO/JsonSerializer.h sceneIO/JsonDeserializer.cpp sceneIO/JsonDeserializer.h sceneIO/SceneReader.cpp sceneIO/SceneReader.h)

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
PUBLIC ../externals/rapidjson/)
