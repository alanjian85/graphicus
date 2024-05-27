#pragma once

#include <vec.hpp>

template <typename T, int N> struct triangle_base {
    vec<T, N> a, b, c;

    triangle_base(vec<T, N> a, vec<T, N> b, vec<T, N> c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

template <typename T, int N> struct triangle : public triangle_base<T, N> {
    using triangle_base<T, N>::triangle_base;

    using triangle_base<T, N>::a;
    using triangle_base<T, N>::b;
    using triangle_base<T, N>::c;
};

template <typename T> struct triangle<T, 2> : public triangle_base<T, 2> {
    using triangle_base<T, 2>::triangle_base;

    using triangle_base<T, 2>::a;
    using triangle_base<T, 2>::b;
    using triangle_base<T, 2>::c;

    vec3<T> barycentric(vec2<T> p) {
        return vec3<T>((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x),
                       (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x),
                       (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x));
    }
};

template <typename T> using triangle2 = triangle<T, 2>;
using triangle2i = triangle2<int>;
using triangle2f = triangle2<float>;

template <typename T> using triangle3 = triangle<T, 3>;
using triangle3i = triangle3<int>;
using traingle3f = triangle3<float>;
