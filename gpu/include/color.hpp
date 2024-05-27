#pragma once

#include <cstdint>

template <typename T> struct basic_color_rgba {
    T r, g, b, a;

    basic_color_rgba() = default;

    basic_color_rgba(T r, T g, T b, T a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

template <typename T> struct color_rgba : public basic_color_rgba<T> {
    using basic_color_rgba<T>::r;
    using basic_color_rgba<T>::g;
    using basic_color_rgba<T>::b;
    using basic_color_rgba<T>::a;

    using basic_color_rgba<T>::basic_color_rgba;
};

template <> struct color_rgba<uint8_t> : public basic_color_rgba<uint8_t> {
    using basic_color_rgba<uint8_t>::r;
    using basic_color_rgba<uint8_t>::g;
    using basic_color_rgba<uint8_t>::b;
    using basic_color_rgba<uint8_t>::a;

    using basic_color_rgba<uint8_t>::basic_color_rgba;

    uint32_t pack() const { return a << 24 | b << 16 | g << 8 | r; }
};

template <> struct color_rgba<float> : public basic_color_rgba<float> {
    using basic_color_rgba<float>::r;
    using basic_color_rgba<float>::g;
    using basic_color_rgba<float>::b;
    using basic_color_rgba<float>::a;

    using basic_color_rgba<float>::basic_color_rgba;

    color_rgba<uint8_t> to_integer_color() const {
        return color_rgba<uint8_t>(r * 255, g * 255, b * 255, a * 255);
    }
};
