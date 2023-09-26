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
        "-O2"
    )
else()
    set(ADDITIONAL_FLAGS
        "/WX"
    )
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if (NOT MSVC)
        set(ADDITIONAL_FLAGS
            "${ADDITIONAL_FLAGS}"
            "-fsanitize=address"
            "-g"
            "-O0"
        )
    else()
        set(ADDITIONAL_FLAGS
            "${ADDITIONAL_FLAGS}"
            "/fsanitize=address"
            "/Od"
        )
    endif()
endif()

message(STATUS "Additional flags ${ADDITIONAL_FLAGS}")


add_library(sources_obj OBJECT ${MAIN_SOURCES})
target_include_directories(sources_obj
    PRIVATE "${PROJECT_SOURCE_DIR}/include"
)
target_compile_options(sources_obj PUBLIC ${ADDITIONAL_FLAGS})
if(WITH_CLANG_TIDY)
    set_target_properties(sources_obj
        PROPERTIES 
            CXX_CLANG_TIDY "clang-tidy;--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy;-p ${PROJECT_BINARY_DIR}"
    )
endif()

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
    OUTPUT_NAME "${OUTNAME}Shared"
    VERSION ${CLEARPNG_VERSION}
)
target_include_directories(ClearPNG_Shared
    INTERFACE "${PROJECT_SOURCE_DIR}/include"
)

# target_compile_options(ClearPNG_Static PUBLIC ${ADDITIONAL_FLAGS})
# target_compile_options(ClearPNG_Shared PUBLIC ${ADDITIONAL_FLAGS})