#ifndef FILE_CLEARPNG_UTIL_H_ALREADY_INCLUDED
#define FILE_CLEARPNG_UTIL_H_ALREADY_INCLUDED

#include <algorithm>
#include <concepts>
#include <type_traits>
#include <utility>

namespace ClearPNG {

namespace Concepts {
// clang-format off

template <typename T>
concept CIntegral = std::is_integral_v<T>;

template <typename T>
concept CFloatingPoint = std::is_floating_point_v<T>;

template <typename T>
concept CNumeric = CIntegral<T> || CFloatingPoint<T>;

template <typename T>
concept CVoid = std::is_void_v<T>;

template <typename T>
concept CAddable = requires(T v, T u) {
    { v == u };
    { v + u };
    { v - u };
    { v += u };
    { v -= u };
};

template <typename T>
concept CIntegralContainer = requires(T v) {
    { CAddable<T> };
    { v.unwrap() } -> CIntegral;
    { v.set(std::declval<int>()) } -> CVoid;
    { T::mask() } -> CIntegral;
};

template <typename T>
concept CFloatContainer = requires(T v) {
    { CAddable<T> };
    { v.unwrap() } -> CFloatingPoint;
    { v.set(std::declval<float>()) } -> CVoid;
};

template<typename T>
concept CRGBPixel = requires(const T& p) {
    { p.unwrapRed() } -> CNumeric;
    { p.unwrapGreen() } -> CNumeric;
    { p.unwrapBlue() } -> CNumeric;
};

template<typename T>
concept CRGBAPixel = requires(const T& p) {
    { CRGBPixel<T> };
    { p.unwrapAlpha() } -> CFloatingPoint;
};

template<typename T>
concept CPixel = CRGBPixel<T> || CRGBAPixel<T>;

template<typename T, typename P>
concept CPixelDistance = requires(T const& d) {
    { d(std::declval<P>(), std::declval<P>()) } -> CFloatingPoint;
};

// clang-format off
}  // end of namespace Concepts

template <typename T>
struct ClampBounds {
    T lower;
    T upper;
};

// clamp allows us to static cast from larger to smaller ints safely
template <typename T>
constexpr T clamp(T const& n, ClampBounds<T> const& bounds)
{
    return std::max(bounds.lower, std::min(n, bounds.upper));
}

[[noreturn]] inline void unreachable()
{
#ifdef __GNUC__  // GCC, Clang, ICC
    __builtin_unreachable();
#elif defined _MSC_VER  // MSVC
    __assume(false);
#endif
}

}  // end of namespace ClearPNG

#endif
