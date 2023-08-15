add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

# create test targets
add_package_test(utest_color ClearPNG_Static utest_color.cpp)

# add tests to ctest
add_test(TestColor utest_color --gtest_color=yes)
