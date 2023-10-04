#include <ClearPNG/color.h>

namespace ClearPNG::Color {

RGBPixel RGBMultiply(RGBPixel const& lhs, RGBPixel const& rhs)
{
    int r = lhs.red.get() * rhs.red.get();
    int g = lhs.green.get() * rhs.green.get();
    int b = lhs.blue.get() * rhs.blue.get();

    return {Red{static_cast<uint8_t>(r / ColorValue<uint8_t>::mask)},
            Green{static_cast<uint8_t>(g / ColorValue<uint8_t>::mask)},
            Blue{static_cast<uint8_t>(b / ColorValue<uint8_t>::mask)}};
}

RGBPixel operator*(RGBPixel const& lhs, RGBPixel const& rhs)
{
    return RGBMultiply(lhs, rhs);
}

RGBPixel& RGBPixel::operator*=(RGBPixel const& other)
{
    auto tmp = RGBMultiply(*this, other);
    red = tmp.red;
    green = tmp.green;
    blue = tmp.blue;

    return *this;
}

RGBPixel RGBScreen(RGBPixel const& lhs, RGBPixel const& rhs)
{
    int r = (ColorValue<uint8_t>::mask - lhs.red.get()) *
            (ColorValue<uint8_t>::mask - rhs.red.get());
    int g = (ColorValue<uint8_t>::mask - lhs.green.get()) *
            (ColorValue<uint8_t>::mask - rhs.green.get());
    int b = (ColorValue<uint8_t>::mask - lhs.blue.get()) *
            (ColorValue<uint8_t>::mask - rhs.blue.get());

    return {Red{static_cast<uint8_t>(ColorValue<uint8_t>::mask -
                                     r / ColorValue<uint8_t>::mask)},
            Green{static_cast<uint8_t>(ColorValue<uint8_t>::mask -
                                       g / ColorValue<uint8_t>::mask)},
            Blue{static_cast<uint8_t>(ColorValue<uint8_t>::mask -
                                      b / ColorValue<uint8_t>::mask)}};
}

}  // end of namespace ClearPNG::Color
