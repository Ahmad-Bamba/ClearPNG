#pragma once

#include "util.h"

#include <cstdint>

namespace ClearPNG {
namespace Color {

template<Numeric T>
struct ColorValue {
    inline T get() const
    {
        return value;
    }

    inline void set(T value)
    {
        this->value = value;
    }

protected:
    T value;
};

struct Red;
struct Green;
struct Blue;

struct Red : ColorValue<uint8_t> {
    explicit Red(uint8_t _r)
    {
        value = _r;
    }


    friend inline bool operator==(Red const& left, Red const& right)
    {
        return left.get() == right.get();
    }

    friend inline bool operator==(Red const&, Green const&)
    {
        return false;
    }
    
    friend inline bool operator==(Red const&, Blue const&)
    {
        return false;
    }

    friend inline Red operator+(Red const& left, Red const& right)
    {
        int sum = left.get() + right.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Red{new_value};
    }

    friend inline Red operator-(Red const& left, Red const& right)
    {
        int difference = left.get() - right.get();
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
    explicit Green(uint8_t _g)
    {
        value = _g;
    }


    friend inline bool operator==(Green const& left, Green const& right)
    {
        return left.get() == right.get();
    }

    friend inline bool operator==(Green const&, Red const&)
    {
        return false;
    }
    
    friend inline bool operator==(Green const&, Blue const&)
    {
        return false;
    }

    friend inline Green operator+(Green const& left, Green const& right)
    {
        int sum = left.get() + right.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Green{new_value};
    }

    friend inline Green operator-(Green const& left, Green const& right)
    {
        int difference = left.get() - right.get();
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
    explicit Blue(uint8_t _b) 
    {
        value = _b;
    }


    friend inline bool operator==(Blue const& left, Blue const& right)
    {
        return left.get() == right.get();
    }

    friend inline bool operator==(Blue const&, Red const&)
    {
        return false;
    }
    
    friend inline bool operator==(Blue const&, Green const&)
    {
        return false;
    }

    friend inline Blue operator+(Blue const& left, Blue const& right)
    {
        int sum = left.get() + right.get();
        uint8_t new_value = clamp(sum, {0, 255});
        return Blue{new_value};
    }

    friend inline Blue operator-(Blue const& left, Blue const& right)
    {
        int difference = left.get() - right.get();
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

} // end of namespace Color
} // end of namespace ClearPNG
