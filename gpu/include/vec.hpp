#pragma once

#include <algorithm>

template <typename T, int N> struct basic_vec {
    T elems[N];

    basic_vec() = default;

    template <typename... Args> basic_vec(Args... args) : elems{args...} {}

    basic_vec &operator=(const basic_vec &other) {
        for (int i = 0; i < N; i++) {
            elems[i] = other.elems[i];
        }
        return *this;
    }
};

template <typename T, int N> struct vec : public basic_vec<T, N> {
    using basic_vec<T, N>::elems;

    using basic_vec<T, N>::basic_vec;

    vec &operator=(const vec &other) {
        return static_cast<vec &>(basic_vec<T, N>::operator=(other));
    }
};

template <typename T> struct vec<T, 2> : public basic_vec<T, 2> {
    using basic_vec<T, 2>::elems;

    T &x = elems[0], &y = elems[1];

    using basic_vec<T, 2>::basic_vec;

    vec &operator=(const vec &other) {
        return static_cast<vec &>(basic_vec<T, 2>::operator=(other));
    }
};

template <typename T> using vec2 = vec<T, 2>;
using vec2i = vec2<int>;
using vec2f = vec2<float>;

template <typename T> struct vec<T, 3> : public basic_vec<T, 3> {
    using basic_vec<T, 3>::elems;

    T &x = elems[0], &y = elems[1], &z = elems[2];

    using basic_vec<T, 3>::basic_vec;

    vec &operator=(const vec &other) {
        return static_cast<vec &>(basic_vec<T, 3>::operator=(other));
    }
};

template <typename T> using vec3 = vec<T, 3>;
using vec3i = vec3<int>;
using vec3f = vec3<float>;
