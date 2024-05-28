#include <gpu.hpp>

#include <color.hpp>
#include <triangle.hpp>
#include <viewport.hpp>

void gpu(uint32_t *mem, uint32_t scrn_size, const float *vertices,
         uint32_t nr_vertices) {
    uint32_t *const fb = mem;
    const uint16_t scrn_width = scrn_size & 0xFFFF;
    const uint16_t scrn_height = scrn_size >> 16;

    viewport vp(scrn_width, scrn_height);
    for (uint16_t y = 0; y < scrn_height; y++) {
        for (uint16_t x = 0; x < scrn_width; x++) {
            fb[y * scrn_width + x] = 0xFF202020;

            for (uint32_t i = 0; i < nr_vertices; i += 6) {
                triangle2f trigf(vec2f(vertices[i + 0], vertices[i + 1]),
                                 vec2f(vertices[i + 2], vertices[i + 3]),
                                 vec2f(vertices[i + 4], vertices[i + 5]));
                auto trig = vp.ndc_to_screen(trigf);

                const auto bary_coord = trig.barycentric(vec2i(x, y));
                if ((bary_coord.x > 0 && bary_coord.y > 0 &&
                     bary_coord.z > 0) ||
                    (bary_coord.x < 0 && bary_coord.y < 0 &&
                     bary_coord.z < 0)) {
                    const auto area = trig.area();
                    color_rgba<float> color(
                        static_cast<float>(bary_coord.x) / area,
                        static_cast<float>(bary_coord.y) / area,
                        static_cast<float>(bary_coord.z) / area, 1.0f);
                    fb[y * scrn_width + x] = color.to_integer_color().pack();
                }
            }
        }
    }
}
