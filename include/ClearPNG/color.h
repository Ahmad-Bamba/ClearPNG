#pragma once

#include <cmath>
#include <cstdint>

#include "util.h"

namespace ClearPNG {

namespace Color {

template <Numeric T>
struct ColorValue {
    inline T get() const { return value; }

    inline void set(T value) { this->value = value; }

    protected:
    T value;
};

struct Red;
struct Green;
struct Blue;

struct Red : ColorValue<uint8_t> {
    explicit Red(uint8_t _r) { value = _r; }

    friend inline bool operator==(Red const& lhs, Red const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Red const&, Green const&) { return false; }

    friend inline bool operator==(Red const&, Blue const&) { return false; }

    friend inline Red operator+(Red const& lhs, Red const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Red{new_value};
    }

    friend inline Red operator-(Red const& lhs, Red const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, 255});
        return Red{new_value};
    }

    inline Red& operator+=(Red const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, 255});
        return *this;
    }

    inline Red& operator-=(Red const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, 255});
        return *this;
    }
};

struct Green : ColorValue<uint8_t> {
    explicit Green(uint8_t _g) { value = _g; }

    friend inline bool operator==(Green const& lhs, Green const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Green const&, Red const&) { return false; }

    friend inline bool operator==(Green const&, Blue const&) { return false; }

    friend inline Green operator+(Green const& lhs, Green const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Green{new_value};
    }

    friend inline Green operator-(Green const& lhs, Green const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, 255});
        return Green{new_value};
    }

    inline Green& operator+=(Green const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, 255});
        return *this;
    }

    inline Green& operator-=(Green const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, 255});
        return *this;
    }
};

struct Blue : ColorValue<uint8_t> {
    explicit Blue(uint8_t _b) { value = _b; }

    friend inline bool operator==(Blue const& lhs, Blue const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Blue const&, Red const&) { return false; }

    friend inline bool operator==(Blue const&, Green const&) { return false; }

    friend inline Blue operator+(Blue const& lhs, Blue const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Blue{new_value};
    }

    friend inline Blue operator-(Blue const& lhs, Blue const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, 255});
        return Blue{new_value};
    }

    inline Blue& operator+=(Blue const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, 255});
        return *this;
    }

    inline Blue& operator-=(Blue const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, 255});
        return *this;
    }
};

struct RGBPixel {
    Red red;
    Green green;
    Blue blue;

    inline bool operator==(RGBPixel const& other) const
    {
        return red == other.red && green == other.green && blue == other.blue;
    }

    inline RGBPixel& operator+=(RGBPixel const& other)
    {
        red += other.red;
        green += other.green;
        blue += other.blue;

        return *this;
    }

    friend inline RGBPixel operator+(RGBPixel const& lhs, RGBPixel const& rhs)
    {
        return RGBPixel(lhs.red + rhs.red, lhs.green + rhs.green,
                        lhs.blue + rhs.blue);
    }

    friend RGBPixel operator*(RGBPixel const&, RGBPixel const&);
    RGBPixel& operator*=(RGBPixel const&);
};

// Blend mode functions
RGBPixel RGBMultiply(RGBPixel const&, RGBPixel const&);
RGBPixel RGBScreen(RGBPixel const&, RGBPixel const&);

enum class Distance_t { EUCLIDEAN, WEIGHTED_EUCLIDEAN, DELTA_E };

// There are potentially many different pixel type and algorithm combinations.
// However, we can imagine calculating pixel distances being in the hot path.
// Therefore, we avoid dynamic dispatch and do compile-time polymorphism with
// CRTP.
template <typename Derived, typename PixelT>
struct CalculateDistanceImpl {
    float operator()(PixelT const& lhs, PixelT const& rhs)
    {
        return (*static_cast<Derived*>(this))(lhs, rhs);
    }
};

template <Distance_t algorithm>
struct RGBDistance
    : public CalculateDistanceImpl<RGBDistance<algorithm>, RGBPixel> {
    // TODO: impl
    float operator()(RGBPixel const& lhs, RGBPixel const& rhs)
    {
        if constexpr (std::is_same_v<algorithm, Distance_t::EUCLIDEAN>) {
            auto red_diff_squared = (lhs.red.get() - rhs.red.get()) *
                                    (lhs.red.get() - rhs.red.get());
            auto green_diff_squared = (lhs.green.get() - rhs.green.get()) *
                                      (lhs.green.get() - rhs.green.get());
            auto blue_diff_squared = (lhs.blue.get() - rhs.blue.get()) *
                                     (lhs.blue.get() - rhs.blue.get());
            return std::sqrt(red_diff_squared + green_diff_squared +
                             blue_diff_squared);
        } else if constexpr (std::is_same_v<algorithm,
                                            Distance_t::WEIGHTED_EUCLIDEAN>) {
            return 1.f;
        } else if constexpr (std::is_same_v<algorithm, Distance_t::DELTA_E>) {
            return 2.f;
        }
    }
};

}  // end of namespace Color
}  // end of namespace ClearPNG
