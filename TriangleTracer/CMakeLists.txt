set(Source_files
    main.cpp)

set(ALL_FILES
    ${Source_files})

add_executable(TriangleTracer ${ALL_FILES})

target_include_directories(TriangleTracer PUBLIC 
    ../Primitives)

target_link_libraries(TriangleTracer Primitives)
