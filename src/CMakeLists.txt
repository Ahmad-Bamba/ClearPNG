set(OUTNAME "clearpng")

set(LIBRARY_SOURCES
    "color.cpp"
    "image.cpp"
)

if (NOT MSVC)
    set(WARNING_FLAGS
        "-Wall"
        "-Wextra"
        "-Wpedantic"
        "-Werror"
    )
else()
    set(WARNING_FLAGS
        "/WX"
    )
endif()

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    if(NOT MVSC)
        set(OPTIMIZE_LEVEL "-O0" "-g")
    else()
        set(OPTIMIZE_LEVEL "/O0" "/Od")
    endif()
else()
    if(NOT MVSC)
        set(OPTIMIZE_LEVEL "-O2")
    else()
        set(OPTIMIZE_LEVEL "/O2")
    endif()
endif()

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    if (NOT MSVC)
        set(SANITIZER_FLAGS
            "-fsanitize=address"
            "-fsanitize=undefined"
            "-fsanitize=leak"
        )
    else()
        set(SANITIZER_FLAGS
            "/fsanitize=address"
        )
    endif()
endif()


add_library(sources_obj OBJECT ${LIBRARY_SOURCES})
target_include_directories(sources_obj
    PRIVATE ${PROJECT_SOURCE_DIR}/include
)
target_compile_options(sources_obj PUBLIC ${WARNING_FLAGS} ${OPTIMIZE_LEVEL} ${SANITIZER_FLAGS})
set_target_properties(sources_obj PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(BUILD_STATIC_ARCHIVE)
    add_library(ClearPNG_
        STATIC
        $<TARGET_OBJECTS:sources_obj>
    )
else()
    add_library(ClearPNG
        SHARED
        $<TARGET_OBJECTS:sources_obj>
    )
endif()

if (CMAKE_BUILD_TYPE STREQUAL Debug AND NOT MVSC)
    target_link_options(ClearPNG
        PUBLIC ${SANITIZER_FLAGS}
    )
endif()

target_include_directories(ClearPNG
    INTERFACE "${PROJECT_SOURCE_DIR}/include"
)
set_target_properties(ClearPNG PROPERTIES
    VERSION ${CLEARPNG_VERSION}
)

if(WITH_CLANG_FORMAT)
    add_custom_target(include-format COMMAND echo "Format headers.")
    FormatDir(include-format ${PROJECT_SOURCE_DIR}/include)
    add_dependencies(ClearPNG include-format)
    FormatDir(ClearPNG ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(WITH_CLANG_TIDY)
    AddClangTidy(sources_obj)
endif()
