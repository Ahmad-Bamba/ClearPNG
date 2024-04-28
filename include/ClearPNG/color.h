#ifndef FILE_CLEARPNG_COLOR_H_ALREADY_INCLUDED
#define FILE_CLEARPNG_COLOR_H_ALREADY_INCLUDED

#include <cinttypes>
#include <cmath>
#include <type_traits>

#include "util.h"

namespace ClearPNG::Color {

template <typename I>
    requires(ClearPNG::Concepts::CIntegral<I>)
class ColorValue {
protected:
    I value{};
    static I constexpr _mask = ~0;

public:
    constexpr ColorValue() = default;
    constexpr explicit ColorValue(I _v) : value{_v} {}
    constexpr ColorValue& operator=(I _v)
    {
        value = _v;
        return *this;
    }

    constexpr void set(I i) { value = i; }
    constexpr I unwrap() const { return value; }

    constexpr bool operator==(ColorValue const& other) const
    {
        return value == other.unwrap();
    }

    constexpr ColorValue operator+(ColorValue const& other) const
    {
        uint64_t sum = value + other.unwrap();
        I new_value = static_cast<I>(
            clamp(sum, {.lower = 0, .upper = ColorValue<I>::_mask}));
        return ColorValue{new_value};
    }

    constexpr ColorValue operator-(ColorValue const& other) const
    {
        int64_t difference = value - other.unwrap();
        I new_value = static_cast<I>(
            clamp(difference, {.lower = 0, .upper = ColorValue::_mask}));
        return ColorValue{new_value};
    }

    constexpr ColorValue& operator+=(ColorValue const& other)
    {
        uint64_t sum = value + other.unwrap();
        value = static_cast<I>(
            clamp(sum, {.lower = 0, .upper = ColorValue::_mask}));
        return *this;
    }

    constexpr ColorValue& operator-=(ColorValue const& other)
    {
        int64_t difference = value - other.unwrap();
        value = static_cast<I>(
            clamp(difference, {.lower = 0, .upper = ColorValue::_mask}));
        return *this;
    }

    static constexpr I mask() { return _mask; }
};

template <typename F>
    requires(ClearPNG::Concepts::CFloatingPoint<F>)
class ColorFloatValue {
protected:
    F value{};

public:
    constexpr ColorFloatValue() = default;
    constexpr explicit ColorFloatValue(F _v) : value{_v} {}
    constexpr ColorFloatValue& operator=(F _v)
    {
        value = _v;
        return *this;
    }

    constexpr void set(F i) { value = i; }
    constexpr F unwrap() const { return value; }

    constexpr bool operator==(ColorFloatValue const& other) const
    {
        return value == other.unwrap();
    }

    constexpr ColorFloatValue operator+(ColorFloatValue const& other) const
    {
        return ColorFloatValue{value + other.unwrap()};
    }

    constexpr ColorFloatValue operator-(ColorFloatValue const& other) const
    {
        return ColorFloatValue{value - other.unwrap()};
    }

    constexpr ColorFloatValue& operator+=(ColorFloatValue const& other)
    {
        value += other.unwrap();
        return *this;
    }

    constexpr ColorFloatValue& operator-=(ColorFloatValue const& other)
    {
        value -= other.unwrap();
        return *this;
    }
};

template <typename S>
    requires(ClearPNG::Concepts::CIntegral<S>)
class UnsizedRed;

template <typename S>
    requires(ClearPNG::Concepts::CIntegral<S>)
class UnsizedGreen;

template <typename S>
    requires(ClearPNG::Concepts::CIntegral<S>)
class UnsizedBlue;

template <typename Size>
    requires(ClearPNG::Concepts::CIntegral<Size>)
class UnsizedRed : public ColorValue<Size> {
public:
    using ColorValue<Size>::ColorValue;

    constexpr bool operator==(UnsizedRed const& other) const
    {
        return this->value == other.unwrap();
    }

    constexpr bool operator==(UnsizedGreen<Size> const&) const { return false; }
    constexpr bool operator==(UnsizedBlue<Size> const&) const { return false; }
};

template <typename Size>
    requires(ClearPNG::Concepts::CIntegral<Size>)
class UnsizedGreen : public ColorValue<Size> {
public:
    using ColorValue<Size>::ColorValue;

    constexpr bool operator==(UnsizedGreen const& other) const
    {
        return this->value == other.unwrap();
    }

    constexpr bool operator==(UnsizedRed<Size> const&) const { return false; }
    constexpr bool operator==(UnsizedBlue<Size> const&) const { return false; }
};

template <typename Size>
    requires(ClearPNG::Concepts::CIntegral<Size>)
class UnsizedBlue : public ColorValue<Size> {
public:
    using ColorValue<Size>::ColorValue;

    constexpr bool operator==(UnsizedBlue const& other) const
    {
        return this->value == other.unwrap();
    }

    constexpr bool operator==(UnsizedGreen<Size> const&) const { return false; }
    constexpr bool operator==(UnsizedRed<Size> const&) const { return false; }
};

template <typename P, typename RedType, typename GreenType, typename BlueType>
    requires(ClearPNG::Concepts::CPixel<P>,
             ClearPNG::Concepts::CIntegralContainer<RedType>,
             ClearPNG::Concepts::CIntegralContainer<GreenType>,
             ClearPNG::Concepts::CIntegralContainer<BlueType>)
constexpr P AddPixels(P const& lhs, P const& rhs)
{
    using IntRed = decltype(lhs.unwrapRed());
    using IntGreen = decltype(lhs.unwrapGreen());
    using IntBlue = decltype(lhs.unwrapBlue());
    uint64_t red_sum = lhs.unwrapRed() + rhs.unwrapRed();
    uint64_t green_sum = lhs.unwrapGreen() + rhs.unwrapGreen();
    uint64_t blue_sum = lhs.unwrapBlue() + rhs.unwrapBlue();
    return {RedType{static_cast<IntRed>(
                clamp(red_sum, {.lower = 0, .upper = RedType::mask()}))},
            GreenType{static_cast<IntGreen>(
                clamp(green_sum, {.lower = 0, .upper = GreenType::mask()}))},
            BlueType{static_cast<IntBlue>(
                clamp(blue_sum, {.lower = 0, .upper = BlueType::mask()}))}};
}

template <typename P, typename RedType, typename GreenType, typename BlueType>
    requires(ClearPNG::Concepts::CPixel<P>,
             ClearPNG::Concepts::CIntegralContainer<RedType>,
             ClearPNG::Concepts::CIntegralContainer<GreenType>,
             ClearPNG::Concepts::CIntegralContainer<BlueType>)
constexpr P MultiplyPixels(P const& lhs, P const& rhs)
{
    using IntRed = decltype(lhs.unwrapRed());
    using IntGreen = decltype(lhs.unwrapGreen());
    using IntBlue = decltype(lhs.unwrapBlue());
    uint64_t red_prod = lhs.unwrapRed() * rhs.unwrapRed();
    uint64_t green_prod = lhs.unwrapGreen() * rhs.unwrapGreen();
    uint64_t blue_prod = lhs.unwrapBlue() * rhs.unwrapBlue();
    return {RedType{static_cast<IntRed>(red_prod / RedType::mask())},
            GreenType{static_cast<IntGreen>(green_prod / GreenType::mask())},
            BlueType{static_cast<IntBlue>(blue_prod / BlueType::mask())}};
}

template <typename P, typename RedType, typename GreenType, typename BlueType>
    requires(ClearPNG::Concepts::CPixel<P>,
             ClearPNG::Concepts::CIntegralContainer<RedType>,
             ClearPNG::Concepts::CIntegralContainer<GreenType>,
             ClearPNG::Concepts::CIntegralContainer<BlueType>)
constexpr P ScreenPixels(P const& lhs, P const& rhs)
{
    int64_t r = (RedType::mask() - lhs.unwrapRed()) *
                (RedType::mask() - rhs.unwrapRed());
    int64_t g = (GreenType::mask() - lhs.unwrapGreen()) *
                (GreenType::mask() - rhs.unwrapGreen());
    int64_t b = (BlueType::mask() - lhs.unwrapBlue()) *
                (BlueType::mask() - rhs.unwrapBlue());

    using IntRed = decltype(lhs.unwrapRed());
    using IntGreen = decltype(lhs.unwrapGreen());
    using IntBlue = decltype(lhs.unwrapBlue());

    return {
        RedType{static_cast<IntRed>(RedType::mask() - r / RedType::mask())},
        GreenType{
            static_cast<IntGreen>(GreenType::mask() - g / RedType::mask())},
        BlueType{static_cast<IntBlue>(BlueType::mask() - b / RedType::mask())}};
}

auto EuclideanPixelDistance =
    [](ClearPNG::Concepts::CPixel auto const& lhs,
       ClearPNG::Concepts::CPixel auto const& rhs) constexpr -> float {
    auto delta_R2 = (lhs.unwrapRed() - rhs.unwrapRed()) *
                    (lhs.unwrapRed() - rhs.unwrapRed());
    auto delta_G2 = (lhs.unwrapGreen() - rhs.unwrapGreen()) *
                    (lhs.unwrapGreen() - rhs.unwrapGreen());
    auto delta_B2 = (lhs.unwrapBlue() - rhs.unwrapBlue()) *
                    (lhs.unwrapBlue() - rhs.unwrapBlue());
    return std::sqrt(delta_R2 + delta_G2 + delta_B2);
};

auto WeightedEuclideanPixelDistance =
    [](ClearPNG::Concepts::CPixel auto const& lhs,
       ClearPNG::Concepts::CPixel auto const& rhs) constexpr -> float {
    auto R_bar = (lhs.unwrapRed() + rhs.unwrapRed()) / 2;
    auto delta_R2 = (lhs.unwrapRed() - rhs.unwrapRed()) *
                    (lhs.unwrapRed() - rhs.unwrapRed());
    auto delta_G2 = (lhs.unwrapGreen() - rhs.unwrapGreen()) *
                    (lhs.unwrapGreen() - rhs.unwrapGreen());
    auto delta_B2 = (lhs.unwrapBlue() - rhs.unwrapBlue()) *
                    (lhs.unwrapBlue() - rhs.unwrapBlue());
    if (R_bar < 128) {
        return std::sqrt(2 * delta_R2 + 4 * delta_G2 + 3 * delta_B2);
    }
    else {
        return std::sqrt(3 * delta_R2 + 4 * delta_G2 + 2 * delta_B2);
    }
};

template <typename P>
    requires(ClearPNG::Concepts::CPixel<P>)
struct CIELABImpl {
    struct CIELAB {
        float Lstar;
        float astar;
        float bstar;
    };
    float operator-(P const&) { return 0.; }
};

template <typename RedType, typename GreenType, typename BlueType>
    requires(ClearPNG::Concepts::CIntegralContainer<RedType>,
             ClearPNG::Concepts::CIntegralContainer<GreenType>,
             ClearPNG::Concepts::CIntegralContainer<BlueType>)
struct UnsizedRGBPixel {
    RedType red;
    GreenType green;
    BlueType blue;

    constexpr bool operator==(UnsizedRGBPixel const& other) const
    {
        return red.unwrap() == other.unwrapRed() &&
               blue.unwrap() == other.unwrapBlue() &&
               green.unwrap() == other.unwrapGreen();
    }

    constexpr auto unwrapRed() const { return red.unwrap(); }

    constexpr auto unwrapGreen() const { return green.unwrap(); }

    constexpr auto unwrapBlue() const { return blue.unwrap(); }

    constexpr UnsizedRGBPixel operator+(UnsizedRGBPixel const& other) const
    {
        return AddPixels<UnsizedRGBPixel, RedType, GreenType, BlueType>(*this,
                                                                        other);
    }

    constexpr UnsizedRGBPixel& operator+=(UnsizedRGBPixel const& other)
    {
        using IntRed = decltype(unwrapRed());
        using IntGreen = decltype(unwrapGreen());
        using IntBlue = decltype(unwrapBlue());

        uint64_t red_sum = unwrapRed() + other.unwrapRed();
        uint64_t green_sum = unwrapGreen() + other.unwrapGreen();
        uint64_t blue_sum = unwrapBlue() + other.unwrapBlue();

        red = RedType{static_cast<IntRed>(
            clamp(red_sum, {.lower = 0, .upper = RedType::mask()}))};
        green = GreenType{static_cast<IntGreen>(
            clamp(green_sum, {.lower = 0, .upper = GreenType::mask()}))};
        blue = BlueType{static_cast<IntBlue>(
            clamp(blue_sum, {.lower = 0, .upper = BlueType::mask()}))};

        return *this;
    }

    constexpr UnsizedRGBPixel operator*(UnsizedRGBPixel const& other) const
    {
        return MultiplyPixels<UnsizedRGBPixel, RedType, GreenType, BlueType>(
            *this, other);
    }

    constexpr UnsizedRGBPixel& operator*=(UnsizedRGBPixel const& other)
    {
        using IntRed = decltype(unwrapRed());
        using IntGreen = decltype(unwrapGreen());
        using IntBlue = decltype(unwrapBlue());

        uint64_t red_prod = unwrapRed() * other.unwrapRed() / RedType::mask();
        uint64_t green_prod =
            unwrapGreen() * other.unwrapGreen() / GreenType::mask();
        uint64_t blue_prod =
            unwrapBlue() * other.unwrapBlue() / BlueType::mask();

        red = RedType{static_cast<IntRed>(
            clamp(red_prod, {.lower = 0, .upper = RedType::mask()}))};
        green = GreenType{static_cast<IntGreen>(
            clamp(green_prod, {.lower = 0, .upper = GreenType::mask()}))};
        blue = BlueType{static_cast<IntBlue>(
            clamp(blue_prod, {.lower = 0, .upper = BlueType::mask()}))};

        return *this;
    }

    constexpr float operator-(UnsizedRGBPixel const& other) const
    {
        return EuclideanPixelDistance(*this, other);
    }
};

// For most images, 8-bit color depth is the default

using Red = UnsizedRed<uint8_t>;
using Green = UnsizedGreen<uint8_t>;
using Blue = UnsizedBlue<uint8_t>;
using RGBPixel = UnsizedRGBPixel<Red, Green, Blue>;

auto constexpr RGBMultiply = MultiplyPixels<RGBPixel, Red, Green, Blue>;
auto constexpr RGBScreen = ScreenPixels<RGBPixel, Red, Green, Blue>;

// Define types for 16-bit color depth too

using Red16 = UnsizedRed<uint16_t>;
using Green16 = UnsizedGreen<uint16_t>;
using Blue16 = UnsizedBlue<uint16_t>;
using RGBPixel16 = UnsizedRGBPixel<Red16, Green16, Blue16>;

auto constexpr RGB16Multiply =
    MultiplyPixels<RGBPixel16, Red16, Green16, Blue16>;
auto constexpr RGB16Screen =
    ScreenPixels<RGBPixel16, Red16, Green16, Blue16>;


// TODO: Think about how to support 24-color images in a way that they play nice
// with the above types.

}  // namespace ClearPNG::Color

#endif
