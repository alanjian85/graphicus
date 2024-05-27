#include <gpu.hpp>

const uint32_t color[8] = {
    0xFFFFFFFF, 0xFF00FFFF, 0xFFFFFF00, 0xFF00FF00,
    0xFFFF00FF, 0xFF0000FF, 0xFFFF0000, 0xFF000000,
};

void gpu(uint32_t *mem) {
    for (int i = 0; i < 600; i++) {
        for (int j = 0; j < 800; j++) {
            mem[i * 800 + j] = color[j / 100];
        }
    }
}