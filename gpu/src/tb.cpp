#include <cstdio>
#include <cstdlib>

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

    bool quit = false;
    uint32_t mem[SCRN_WIDTH * SCRN_HEIGHT];
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        gpu(mem, SCRN_WIDTH | SCRN_HEIGHT << 16);

        SDL_RenderClear(renderer);

        SDL_UpdateTexture(fb_texture, nullptr, mem, 800 * 4);
        SDL_RenderCopy(renderer, fb_texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(fb_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}