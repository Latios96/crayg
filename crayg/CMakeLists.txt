set(crayg_SRCS
        Vector3f.h
        Vector3f.cpp
        Image.h
        Image.cpp
        BmpImageWriter.h
        BmpImageWriter.cpp
        Camera.h
        Camera.cpp
        PineHoleCameraModel.h
        PineHoleCameraModel.cpp
        Ray.h
        Ray.cpp
        Intersectable.h
        Sphere.h
        Sphere.cpp
        Color.h
        Color.cpp
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
        schemas/ImageablePrim.cpp)

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
