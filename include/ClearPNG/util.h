#pragma once

#include <algorithm>
#include <type_traits>

namespace ClearPNG {

template <typename T>
concept Numeric = std::is_integral_v<T> || std::is_floating_point_v<T>;

template <typename T>
struct ClampBounds {
    T lower;
    T upper;
};

template <typename T>
T clamp(T const& n, ClampBounds<T> const& bounds)
{
    return std::max(bounds.lower, std::min(n, bounds.upper));
}

}  // end of namespace ClearPNG
