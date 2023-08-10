#include "ClearPNG/color.h"

#include <gtest/gtest.h>
#include <cstdint>

using namespace ClearPNG::Color;

// test basic RGB color arithmetic
TEST(TestColor, RGBColorArithmetic)
{
    // Create RGB values
    Red red { 100 };
    Green green { 100 };
    Blue blue { 100 };

    // Test that addition for RGB colors is clamped at 255
    ASSERT_EQ(red + Red{220}, Red{255});
    ASSERT_EQ(green + Green{220}, Green{255});
    ASSERT_EQ(blue + Blue{220}, Blue{255});

    // Test that subtraction for colors is clamped at 0
    ASSERT_EQ(red - Red{220}, Red{0});
    ASSERT_EQ(green - Green{220}, Green{0});
    ASSERT_EQ(blue - Blue{220}, Blue{0});

    // Test that += -= works as expected
    red += Red{1};
    green += Green{1};
    blue += Blue{1};

    ASSERT_EQ(red, Red{101});
    ASSERT_EQ(green, Green{101});
    ASSERT_EQ(blue, Blue{101});

    red -= Red{1};
    blue -= Blue{1};
    green -= Green{1};

    ASSERT_EQ(red, Red{100});
    ASSERT_EQ(green, Green{100});
    ASSERT_EQ(blue, Blue{100});

    // Test that Red, Green, and Blue are zero cost abstractions
    ASSERT_EQ(sizeof(red), sizeof(uint8_t));
    ASSERT_EQ(sizeof(green), sizeof(uint8_t));
    ASSERT_EQ(sizeof(blue), sizeof(uint8_t));
}

TEST(TestColor, RGBPixelArithmetic)
{
    ASSERT_TRUE(1);
}