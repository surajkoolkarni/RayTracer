set(Source_files
    main.cpp)

set(ALL_FILES
    ${Source_files})

add_executable(ModelTracer ${ALL_FILES})

target_include_directories(ModelTracer PUBLIC 
    ../Model
    ../RayTracer)

target_link_libraries(ModelTracer Model
    RayTracer
    stb_image)
    