#pragma once

#include <vec.hpp>

template <typename T, int N> struct basic_triangle {
    vec<T, N> a, b, c;

    basic_triangle(vec<T, N> a, vec<T, N> b, vec<T, N> c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};

template <typename T, int N> struct triangle : public basic_triangle<T, N> {
    using basic_triangle<T, N>::basic_triangle;

    using basic_triangle<T, N>::a;
    using basic_triangle<T, N>::b;
    using basic_triangle<T, N>::c;
};

template <typename T> struct triangle<T, 2> : public basic_triangle<T, 2> {
    using basic_triangle<T, 2>::basic_triangle;

    using basic_triangle<T, 2>::a;
    using basic_triangle<T, 2>::b;
    using basic_triangle<T, 2>::c;

    T area() const {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    vec3<T> barycentric(const vec2<T> &p) const {
        return vec3<T>((c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x),
                       (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x),
                       (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
    }
};

template <typename T> using triangle2 = triangle<T, 2>;
using triangle2i = triangle2<int>;
using triangle2f = triangle2<float>;

template <typename T> using triangle3 = triangle<T, 3>;
using triangle3i = triangle3<int>;
using traingle3f = triangle3<float>;
