set(Header_files
    FacetTriangle.h
    Image.h
    IObject.h
    Material.h
    PrimitivesApi.h
    Ray.h
    Sphere.h
    Transform.h
    Triangle.h
    Utils.h
    Vertex.h
    )

set(Source_files
    FacetTriangle.cpp
    IObject.cpp
    Sphere.cpp
    Transform.cpp
    Triangle.cpp
    Utils.cpp
    Vertex.cpp
    )

set(ALL_FILES
    ${Header_files}
    ${Source_files})

add_library(Primitives SHARED ${ALL_FILES})