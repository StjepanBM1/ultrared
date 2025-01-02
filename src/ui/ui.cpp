
#include "ui.hpp"

void _ui_end_level_screen(SDL_Window *__m__window, SDL_Renderer *__m__renderer,
                          SDL_Surface *__m__surface, SDL_Texture *__m__texture)
{

    if (TTF_Init() == -1) {
        printf("[UR] TTF_Init: %s\n", TTF_GetError());
        return;
    }

    SDL_SetRenderDrawColor(__m__renderer, 0, 0, 0, 255);
    SDL_RenderClear(__m__renderer);

    TTF_Font *font = TTF_OpenFont("data/fonts/done.ttf", 24);
    if (!font) {
        printf("[UR] TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    // Create text to display
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "level finished. any key to quit.", white);
    if (!text_surface) {
        printf("[UR] TTF_RenderText_Solid: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(__m__renderer, text_surface);
    SDL_FreeSurface(text_surface);

    int text_width, text_height;
    SDL_QueryTexture(text_texture, NULL, NULL, &text_width, &text_height);
    SDL_Rect text_rect = {
        SCREEN_WIDTH / 2 - text_width / 2,
        SCREEN_HEIGHT / 2 - text_height / 2,
        text_width,
        text_height
    };

    SDL_RenderCopy(__m__renderer, text_texture, NULL, &text_rect);
    SDL_RenderPresent(__m__renderer);

    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Event event;
    while (true) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
            __r_quit__();
        }
    }
}
