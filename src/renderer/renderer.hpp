
#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "../io/log.hpp"

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct DATA
{
    uint8_t map_data[8 * 8];
    int position;
    int heading;
};

// main rendering functions
void __r_init__();
void __r_loop__(DATA data);
int __r_quit__();

#endif // !RENDERER_HPP
