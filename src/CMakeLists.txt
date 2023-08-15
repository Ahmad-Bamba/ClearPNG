set(OUTNAME "clearpng")

set(MAIN_SOURCES
    "color.cpp"
)

if (NOT MSVC)
    set(ADDITIONAL_FLAGS
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Werror"
    )
else()
    set(ADDITIONAL_FLAGS
        "/W4"
        "/WX"
    )
endif()

message(STATUS "Additional flags ${ADDITIONAL_FLAGS}")

add_compile_options(${ADDITIONAL_FLAGS})


add_library(sources_obj OBJECT ${MAIN_SOURCES})
target_include_directories(sources_obj
    PRIVATE "${PROJECT_SOURCE_DIR}/include"
)

add_library(ClearPNG_Static
    STATIC
    $<TARGET_OBJECTS:sources_obj>
)

add_library(ClearPNG_Shared
    SHARED
    $<TARGET_OBJECTS:sources_obj>
)

set_target_properties(ClearPNG_Static PROPERTIES
    OUTPUT_NAME ${OUTNAME}
)
target_include_directories(ClearPNG_Static
    INTERFACE "${PROJECT_SOURCE_DIR}/include"
)
set_target_properties(ClearPNG_Shared PROPERTIES
    OUTPUT_NAME ${OUTNAME}
    VERSION ${CLEARPNG_VERSION}
)
target_include_directories(ClearPNG_Shared
    INTERFACE "${PROJECT_SOURCE_DIR}/include"
)

# target_compile_options(ClearPNG_Static PUBLIC ${ADDITIONAL_FLAGS})
# target_compile_options(ClearPNG_Shared PUBLIC ${ADDITIONAL_FLAGS})