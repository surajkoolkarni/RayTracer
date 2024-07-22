set(PROJECT_NAME SphereRayTracer)

################################################################################
# Source groups
################################################################################
set(Source_Files
    "main.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

################################################################################
# Dependencies
################################################################################
# Link with other targets.

target_include_directories(SphereRayTracer PUBLIC
    ../RayTracer
)

target_link_libraries(${PROJECT_NAME}
    Model
    RayTracer
    stb_image
)
