#pragma once

#include <triangle.hpp>
#include <vec.hpp>

struct viewport {
    int width, height;

    viewport() = default;

    viewport(int width, int height) {
        this->width = width;
        this->height = height;
    }

    vec2i ndc_to_screen(vec2f v) const {
        return vec2i(static_cast<int>((v.x + 1) * 0.5f * width),
                     static_cast<int>((v.y + 1) * 0.5f * height));
    }

    triangle2i ndc_to_screen(triangle2f t) const {
        return triangle2i(ndc_to_screen(t.a), ndc_to_screen(t.b),
                          ndc_to_screen(t.c));
    }
};
