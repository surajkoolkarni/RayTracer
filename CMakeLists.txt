cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(RayTracer CXX)

add_subdirectory(RayTracer)
add_subdirectory(SphereRayTracer)
add_subdirectory(TriangleTracer)
add_subdirectory(ModelTracer)

add_subdirectory(Primitives)
add_subdirectory(Model)
add_subdirectory(stb_image)

find_package(assimp)
find_package(glm)
