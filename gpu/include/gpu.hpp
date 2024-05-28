#pragma once

#include <cstdint>

void gpu(uint32_t *mem, uint32_t scrn_size, const float *vertices,
         uint32_t nr_vertices);