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
    RGBPixel p1(Red{10}, Green{102}, Blue{204});
    RGBPixel p2(Red{255}, Green{242}, Blue{179});
    RGBPixel p3(Red{191}, Green{150}, Blue{61});

    RGBPixel const WHITE(Red{255}, Green{255}, Blue{255});
    RGBPixel const BLACK(Red{0}, Green{0}, Blue{0});

    // Test that we can perform RGB pixel equality
    ASSERT_EQ(p1, RGBPixel(Red{10}, Green{102}, Blue{204}));

    // Test RGB pixel add
    ASSERT_EQ(p1 + p2, RGBPixel(Red{255}, Green{255}, Blue{255}));
    auto p4 = p1;
    p4 += RGBPixel(Red{1}, Green{1}, Blue{1});
    ASSERT_EQ(p4, RGBPixel(Red{11}, Green{103}, Blue{205}));

    // Test RGB pixel multiply
    ASSERT_EQ(p1 * p2, RGBPixel(Red{10}, Green{96}, Blue{143}));
    // Test that multiplying by a white pixel leaves the pixel the same
    auto p5 = p1;
    p5 *= WHITE;
    ASSERT_EQ(p5, p1);
    // Test that multiplying by a black pixel makes the pixel black
    p5 *= BLACK;
    ASSERT_EQ(p5, BLACK);

    // Test RGB pixel screen
    ASSERT_EQ(RGBScreen(p1, p3), RGBPixel(Red{194}, Green{192}, Blue{217}));
    // Test that screening with black leaves the pixel alone
    ASSERT_EQ(RGBScreen(p1, BLACK), p1);
    // Test that screening with white results in white
    ASSERT_EQ(RGBScreen(p1, WHITE), WHITE);
}

TEST(TestColor, RGBDistances)
{
    ASSERT_EQ(1, 1);

    // TODO: Test RGB pixel distance formulas

    // ASSERT_FLOAT_EQ(RGBDistance())
}
