set(Header_files
    Mesh.h
    Model.h
    ModelApi.h
    )

set(Source_files
    Mesh.cpp
    Model.cpp
    )

set(ALL_FILES
    ${Header_files}
    ${Source_files})

add_library(Model SHARED ${ALL_FILES})

target_include_directories(Model PUBLIC
    ../Primitives
    ../stb_image
)

target_link_libraries(Model assimp)