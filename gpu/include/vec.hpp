#pragma once

template <typename T, int N> struct vec;

template <typename T> struct vec<T, 2> {
    T x, y;

    vec() = default;

    vec(T x, T y) {
        this->x = x;
        this->y = y;
    }
};

template <typename T> using vec2 = vec<T, 2>;
using vec2i = vec2<int>;
using vec2f = vec2<float>;

template <typename T> struct vec<T, 3> {
    T x, y, z;

    vec() = default;

    vec(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

template <typename T> using vec3 = vec<T, 3>;
using vec3i = vec3<int>;
using vec3f = vec3<float>;
