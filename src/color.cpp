#include <ClearPNG/color.h>

namespace ClearPNG {

namespace Color {

RGBPixel RGBMultiply(RGBPixel const& lhs, RGBPixel const& rhs)
{
    int r = lhs.red.get() * rhs.red.get();
    int g = lhs.green.get() * rhs.green.get();
    int b = lhs.blue.get() * rhs.blue.get();

    return RGBPixel(
        Red{static_cast<uint8_t>(r / 255)},
        Green{static_cast<uint8_t>(g / 255)},
        Blue{static_cast<uint8_t>(b / 255)}
    );
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
    int r = (255 - lhs.red.get()) * (255 - rhs.red.get());
    int g = (255 - lhs.green.get()) * (255 - rhs.green.get());
    int b = (255 - lhs.blue.get()) * (255 - rhs.blue.get());

    return RGBPixel(
        Red{static_cast<uint8_t>(255 - r / 255)},
        Green{static_cast<uint8_t>(255 - g / 255)},
        Blue{static_cast<uint8_t>(255 - b / 255)}
    );
}

} // end of namespace Color
} // end of namespace ClearPNG