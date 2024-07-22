set(PROJECT_NAME RayTracer)

set(PROJECT_DIR ./RayTracer)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "IRayCaster.h"
    "ModelRayCaster.h"
    "RayCast.h"
    "RayTracerExport.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "IRayCaster.cpp"
    "ModelRayCaster.cpp"
    "RayCast.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################

add_library(RayTracer SHARED ${ALL_FILES})

target_include_directories(RayTracer PUBLIC 
    ../Primitives
    ../Model
    ../stb_image)

target_link_libraries(RayTracer Primitives
    Model
    assimp)
