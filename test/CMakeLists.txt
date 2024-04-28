add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

# create test targets and add to CTest
add_package_test(utest_color ClearPNG utest_color.cpp)

if (NOT MSVC)
    target_compile_options(utest_color PRIVATE "-fsanitize=undefined")
    target_link_libraries(utest_color "-fsanitize=undefined")
endif()

