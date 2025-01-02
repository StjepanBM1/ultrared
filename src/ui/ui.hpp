
#ifndef UI_HPP
#define UI_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../renderer/renderer.hpp"
#include "../io/log.hpp"

void _ui_end_level_screen(SDL_Window *__m__window, SDL_Renderer *__m__renderer,
                          SDL_Surface *__m__surface, SDL_Texture *__m__texture);

#endif//UI_HPP
