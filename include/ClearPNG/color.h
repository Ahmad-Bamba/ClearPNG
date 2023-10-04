#pragma once

#include <cmath>
#include <cstdint>

#include "util.h"

namespace ClearPNG::Color {

template <Numeric T>
struct ColorValue {
    inline T get() const { return value; }

    inline void set(T value) { this->value = value; }

    static constexpr T mask = ~0;

    protected:
    T value;
};

struct Red;
struct Green;
struct Blue;

struct Red : public ColorValue<uint8_t> {
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
        uint8_t new_value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return Red{new_value};
    }

    friend inline Red operator-(Red const& lhs, Red const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, ColorValue<uint8_t>::mask});
        return Red{new_value};
    }

    inline Red& operator+=(Red const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Red& operator-=(Red const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, ColorValue<uint8_t>::mask});
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
        uint8_t new_value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return Green{new_value};
    }

    friend inline Green operator-(Green const& lhs, Green const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, ColorValue<uint8_t>::mask});
        return Green{new_value};
    }

    inline Green& operator+=(Green const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Green& operator-=(Green const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, ColorValue<uint8_t>::mask});
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
        uint8_t new_value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return Blue{new_value};
    }

    friend inline Blue operator-(Blue const& lhs, Blue const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value = clamp(difference, {0, ColorValue<uint8_t>::mask});
        return Blue{new_value};
    }

    inline Blue& operator+=(Blue const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {0, ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Blue& operator-=(Blue const& other)
    {
        int difference = value - other.get();
        value = clamp(difference, {0, ColorValue<uint8_t>::mask});
        return *this;
    }
};

struct RGBPixel {
    Red red;
    Green green;
    Blue blue;

    RGBPixel(Red _r, Green _g, Blue _b) : red{_r}, green{_g}, blue{_b} {}

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
    float operator()(PixelT const& lhs, PixelT const& rhs) noexcept
    {
        return (*static_cast<Derived*>(this))(lhs, rhs);
    }
};

template <Distance_t algorithm>
struct RGBDistance
    : public CalculateDistanceImpl<RGBDistance<algorithm>, RGBPixel> {
    float operator()(RGBPixel const& lhs, RGBPixel const& rhs) noexcept
    {
        if constexpr (algorithm == Distance_t::EUCLIDEAN) {
            auto delta_R2 = (lhs.red.get() - rhs.red.get()) *
                            (lhs.red.get() - rhs.red.get());
            auto delta_G2 = (lhs.green.get() - rhs.green.get()) *
                            (lhs.green.get() - rhs.green.get());
            auto delta_B2 = (lhs.blue.get() - rhs.blue.get()) *
                            (lhs.blue.get() - rhs.blue.get());
            return std::sqrt(delta_R2 + delta_G2 + delta_B2);
        } else if constexpr (algorithm == Distance_t::WEIGHTED_EUCLIDEAN) {
            auto R_bar = (lhs.red.get() + rhs.red.get()) / 2;
            auto delta_R2 = (lhs.red.get() - rhs.red.get()) *
                            (lhs.red.get() - rhs.red.get());
            auto delta_G2 = (lhs.green.get() - rhs.green.get()) *
                            (lhs.green.get() - rhs.green.get());
            auto delta_B2 = (lhs.blue.get() - rhs.blue.get()) *
                            (lhs.blue.get() - rhs.blue.get());
            if (R_bar < 128) {
                return std::sqrt(2 * delta_R2 + 4 * delta_G2 + 3 * delta_B2);
            } else {
                return std::sqrt(3 * delta_R2 + 4 * delta_G2 + 2 * delta_B2);
            }
        } else if constexpr (algorithm == Distance_t::DELTA_E) {
            return 2.f;
        }
        unreachable();  // reaching this state is UB
        return 0.;
    }
};

}  // end of namespace ClearPNG::Color
