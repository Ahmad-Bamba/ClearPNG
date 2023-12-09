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
    explicit Red(uint8_t _r) noexcept { value = _r; }

    friend inline bool operator==(Red const& lhs, Red const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Red const&, Green const&) { return false; }

    friend inline bool operator==(Red const&, Blue const&) { return false; }

    friend inline Red operator+(Red const& lhs, Red const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value =
            clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Red{new_value};
    }

    friend inline Red operator-(Red const& lhs, Red const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Red{new_value};
    }

    inline Red& operator+=(Red const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Red& operator-=(Red const& other)
    {
        int difference = value - other.get();
        value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }
};

struct Green : ColorValue<uint8_t> {
    explicit Green(uint8_t _g) noexcept { value = _g; }

    friend inline bool operator==(Green const& lhs, Green const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Green const&, Red const&) { return false; }

    friend inline bool operator==(Green const&, Blue const&) { return false; }

    friend inline Green operator+(Green const& lhs, Green const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value =
            clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Green{new_value};
    }

    friend inline Green operator-(Green const& lhs, Green const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Green{new_value};
    }

    inline Green& operator+=(Green const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Green& operator-=(Green const& other)
    {
        int difference = value - other.get();
        value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }
};

struct Blue : ColorValue<uint8_t> {
    explicit Blue(uint8_t _b) noexcept { value = _b; }

    friend inline bool operator==(Blue const& lhs, Blue const& rhs)
    {
        return lhs.get() == rhs.get();
    }

    friend inline bool operator==(Blue const&, Red const&) { return false; }

    friend inline bool operator==(Blue const&, Green const&) { return false; }

    friend inline Blue operator+(Blue const& lhs, Blue const& rhs)
    {
        int sum = lhs.get() + rhs.get();
        uint8_t new_value =
            clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Blue{new_value};
    }

    friend inline Blue operator-(Blue const& lhs, Blue const& rhs)
    {
        int difference = lhs.get() - rhs.get();
        uint8_t new_value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return Blue{new_value};
    }

    inline Blue& operator+=(Blue const& other)
    {
        int sum = value + other.get();
        value = clamp(sum, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }

    inline Blue& operator-=(Blue const& other)
    {
        int difference = value - other.get();
        value =
            clamp(difference, {.lower = 0, .upper = ColorValue<uint8_t>::mask});
        return *this;
    }
};

struct RGBPixel {
    Red red;
    Green green;
    Blue blue;

    RGBPixel(Red _r, Green _g, Blue _b) noexcept : red{_r}, green{_g}, blue{_b}
    {
    }

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

    // A default distance operator
    friend float operator-(RGBPixel const&, RGBPixel const&);
};

// Blend mode functions
RGBPixel RGBMultiply(RGBPixel const&, RGBPixel const&);
RGBPixel RGBScreen(RGBPixel const&, RGBPixel const&);

enum class Distance_t { EUCLIDEAN, WEIGHTED_EUCLIDEAN, CIELAB };

// There are potentially many different pixel type and algorithm combinations.
// However, we can imagine calculating pixel distances being in the hot path.
// Therefore, we avoid dynamic dispatch and do compile-time polymorphism with
// CRTP.
//
// TODO: PixelT should be some kind of concept
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
    float operator()(RGBPixel const& lhs, RGBPixel const& rhs)
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
        } else if constexpr (algorithm == Distance_t::CIELAB) {
            // convert RGB to CIEXYZ
            struct XYZ {
                float X, Y, Z;
            };
            auto rgb_xyz = [](RGBPixel const& p) -> XYZ {
                float _r = p.red.get() / p.red.mask;
                float _g = p.green.get() / p.green.mask;
                float _b = p.blue.get() / p.blue.mask;

                _r = _r > 0.04045 ? std::pow((_r + 0.055) / 1.055, 2.4)
                                  : _r / 12.92;
                _g = _g > 0.04045 ? std::pow((_g + 0.055) / 1.055, 2.4)
                                  : _g / 12.92;
                _b = _b > 0.04045 ? std::pow((_b + 0.055) / 1.055, 2.4)
                                  : _b / 12.92;

                float X = _r * 0.4124 + _g * 0.3576 + _b * 0.1805;
                float Y = _r * 0.2126 * _g * 0.7152 + _b * 0.0722;
                float Z = _r * 0.0193 + _g * 0.1192 + _b * 0.9505;

                X *= 100;
                Y *= 100;
                Z *= 100;

                return XYZ{X, Y, Z};
            };

            XYZ lhs_xyz = rgb_xyz(lhs);
            XYZ rhs_xyz = rgb_xyz(rhs);

            // convert CIEXYZ to CIELAB
            struct LABstar {
                float CIE_Lstar, CIE_astar, CIE_bstar;
            };
            auto xyz_lab = [](XYZ const& p) -> LABstar {
                // based on D65 reference white, daylight
                float constexpr refX = 94.811;
                float constexpr refY = 100.;
                float constexpr refZ = 107.304;

                float _x = p.X / refX;
                float _y = p.Y / refY;
                float _z = p.Z / refZ;

                _x = _x > 0.008856 ? std::pow(_x, 1.f / 3)
                                   : (7.787 * _x) + (16.f / 116);
                _y = _y > 0.008856 ? std::pow(_y, 1.f / 3)
                                   : (7.787 * _y) + (16.f / 116);
                _z = _z > 0.008856 ? std::pow(_z, 1.f / 3)
                                   : (7.787 * _z) + (16.f / 116);

                float L = (116 * _y) - 16;
                // TODO: Consider if clamping to -128 to 127 is better here
                float a = 500 * (_x - _y);
                float b = 200 * (_y - _z);

                return LABstar{L, a, b};
            };
            LABstar lhs_lab = xyz_lab(lhs_lab);
            LABstar rhs_lab = xyz_lab(rhs_xyz);

            auto deltaLstar = lhs_lab.CIE_Lstar - rhs_lab.CIE_Lstar;
            auto deltaastar = lhs_lab.CIE_astar - rhs_lab.CIE_astar;
            auto deltabstar = lhs_lab.CIE_bstar - rhs_lab.CIE_bstar;

            // calculate distance
            return std::sqrt(deltaLstar * deltaLstar + deltaastar * deltaastar +
                             deltabstar * deltabstar);
        }
        unreachable();  // reaching this state is UB
        return 0.;
    }
};

template <typename T, typename PixelT>
float distance(CalculateDistanceImpl<T, PixelT> impl, PixelT const& lhs,
               PixelT const& rhs)
{
    return impl(lhs, rhs);
}

}  // end of namespace ClearPNG::Color
