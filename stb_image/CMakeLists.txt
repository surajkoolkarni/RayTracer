set(Header_files
    stb_image.h
    stb_image_write.h
    )

set(Source_files
    stb_image.cpp
    )

set(ALL_FILES
    ${Header_files}
    ${Source_files})

if (MSVC)
    add_library(stb_image STATIC ${ALL_FILES})
endif()

if (UNIX)
    add_library(stb_image SHARED ${ALL_FILES})
endif()
