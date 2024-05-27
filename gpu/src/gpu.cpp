#include <gpu.hpp>

#include <triangle.hpp>

void gpu(uint32_t *mem, uint32_t scrn_size) {
    uint32_t *const fb = mem;
    const uint16_t scrn_width = scrn_size & 0xFFFF;
    const uint16_t scrn_height = scrn_size >> 16;

    triangle2i trig(vec2i(400, 150), vec2i(200, 450), vec2i(600, 450));

    for (int y = 0; y < scrn_height; y++) {
        for (int x = 0; x < scrn_width; x++) {
            fb[y * scrn_width + x] = 0xFF202020;

            auto bary_coord = trig.barycentric(vec2i(x, y));
            if ((bary_coord.x > 0 && bary_coord.y > 0 && bary_coord.z > 0) ||
                (bary_coord.x < 0 && bary_coord.y < 0 && bary_coord.z < 0)) {
                fb[y * scrn_width + x] = 0xFF0000FF;
            }
        }
    }
}
