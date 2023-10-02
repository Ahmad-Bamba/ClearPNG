cmake_minimum_required(VERSION 3.12)

set(CLEARPNG_VERSION "0.0.1")

# Set project info
cmake_policy(SET CMP0048 NEW)
project(
    clearpng
    LANGUAGES CXX 
    VERSION ${CLEARPNG_VERSION}
    DESCRIPTION "PNG parser written in modern C++ with 2D shader support"
)

# set CMake module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# set C++ version
set(CMAKE_CXX_STANDARD 20 CACHE STRING "Force compilation with C++20")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# export compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default options
option(WITH_CLANG_TIDY "Should clang-tidy checks be enabled?" OFF)
option(TIDY_EXTRA "If we are using clang-tidy, should extra static analysis checks be performed?" OFF)
option(WITH_CLANG_FORMAT "Should the code be auto-formated with clang-format?" OFF)
option(BUILD_STATIC_ARCHIVE "Should the static archive of ClearPNG be built and installed over the dynamic library?" OFF)
option(BUILD_DOCS "Should the documentation be built?" ON)
option(PACKAGE_TESTS "Build the tests" ON)

# Clang-Format and Clang-Tidy
if (WITH_CLANG_FORMAT)
    include(Format)
endif()
if(WITH_CLANG_TIDY)
    include(Tidy)
endif()

# OpenCL used for SIMD shader support. SIMD shaders will not be
# built or included if OpenCL is not found
find_package(OpenCL)

# Force all libraries to be compiled with /MD for Windows. 
# This avoid very confusing linker errors, especially around 
# Google Test
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL Debug)
        add_compile_options("/MDd")
    else()
        add_compile_options("/MD")
    endif()
endif()

# Main library source
add_subdirectory(src)

if(PACKAGE_TESTS)
    include(CTest)
    include(GoogleTest)
    include(AddPackageTest)
    add_subdirectory(test)
endif()

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

# Build documentation if this is the top-level project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_DOCS)
    find_package(Doxygen)
    if(Doxygen_FOUND)
        add_subdirectory(docs)
    else()
        message(STATUS "Doxygen not found, not building docs.")
    endif()
endif()
