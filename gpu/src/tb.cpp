#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include <gpu.hpp>

const int SCRN_WIDTH = 800;
const int SCRN_HEIGHT = 600;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Failed to initialize SDL\n");
        return EXIT_FAILURE;
    }

    SDL_Window *window =
        SDL_CreateWindow("Graphicus", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, SCRN_WIDTH, SCRN_HEIGHT, 0);
    if (window == nullptr) {
        fprintf(stderr, "Failed to create the window\n");
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        fprintf(stderr, "Failed to create the renderer\n");
        return EXIT_FAILURE;
    }

    SDL_Texture *fb_texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
                          SDL_TEXTUREACCESS_STREAMING, SCRN_WIDTH, SCRN_HEIGHT);
    if (fb_texture == nullptr) {
        fprintf(stderr, "Failed to create the framebuffer texture\n");
        return EXIT_FAILURE;
    }

    const std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f,
        -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f, 0.5f,
    };

    uint32_t mem[SCRN_WIDTH * SCRN_HEIGHT];

    bool quit = false;
    Uint64 start_counter = SDL_GetPerformanceCounter();

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        gpu(mem, SCRN_WIDTH | SCRN_HEIGHT << 16, vertices.data(),
            vertices.size());

        SDL_RenderClear(renderer);

        SDL_UpdateTexture(fb_texture, nullptr, mem, 800 * 4);
        SDL_RenderCopy(renderer, fb_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);

        Uint64 end_counter = SDL_GetPerformanceCounter();
        float frame_time = static_cast<float>(end_counter - start_counter) /
                           SDL_GetPerformanceFrequency();
        SDL_SetWindowTitle(
            window,
            ("Graphicus, FPS: " + std::to_string(1 / frame_time)).c_str());
        start_counter = end_counter;
    }

    SDL_DestroyTexture(fb_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
