
/**
 * TODO:
 * add win / end level tiles.
 */

#include "renderer.hpp"

// variables
SDL_Window *__m__window;        // main window
SDL_Renderer *__m__renderer;    // main renderer
SDL_Surface *__m__surface;      // main surface
SDL_Texture *__m__texture;      // main texture

const int center_x = SCREEN_WIDTH / 2;
const int center_y = SCREEN_HEIGHT / 2;

uint32_t buffer[SCREEN_WIDTH * SCREEN_HEIGHT];  // frame buffer

static uint8_t visible[8];

// global navigation variables
int FRONTAL_WALL = +8;
int LEFT_WALL = 1;
int RIGHT_WALL = +1;

int LEFT = 1;
int RIGHT = 1;
int FORW = 8;
int BACK = 8;

void copy_array(uint8_t data[8*8], uint8_t visible[8], int offset)
{
    for (int i = 0; i < 8; i++)
        visible[i] = data[i+offset];
}

void set_visible(uint8_t data[8 * 8], uint32_t buffer[SCREEN_WIDTH * SCREEN_HEIGHT], int position) 
{

    uint32_t color_left = 0xFFFFFFFF;
    uint32_t color_right = 0xFFFFFFFF;

    if (data[position - LEFT_WALL] == 0)
        printf("[UR] blank space found.\n");

    switch (data[position - LEFT_WALL]) {
        case 0:
            color_left = 0x00000000;
            break;
        
        case 1: 
            color_left = 0xB22222;
            break;
        
        case 2: 
            color_left = 0xFFFF0000;
            break;
        
        case 3:
            color_left = 0x0000FFFF;
            break;
        
        case 4:
            color_left = 0x00FFF00F;
            break;

        default:
            color_right = 0xFFFFFFFF;
            break;
    }

    if (data[position + RIGHT_WALL] == 0)
        printf("[UR] blank space found.\n");

    switch (data[position + RIGHT_WALL]) {
        case 0:
            color_right = 0x00000000;
            break;
        
        case 1:
            color_right = 0xB22222;
            break;
        
        case 2:
            color_right = 0xFFFF0000;
            break;
        
        case 3:
            color_right = 0x0000FFFF;
            break;
        
        case 4:
            color_right = 0x00FFF00F;
            break;
        
        default:
            color_right = 0xFFFFFFFF;
            break;
    }

    for (int x = 0; x < SCREEN_WIDTH; ++x) {
        int height;
        if (x < SCREEN_WIDTH / 2) {
            int distance_from_center = x;
            height = SCREEN_HEIGHT - (distance_from_center * 1.5);
            if (height < 0) height = 0;
        } else {
            int distance_from_center = SCREEN_WIDTH - 1 - x;
            height = SCREEN_HEIGHT - (distance_from_center * 1.5);
            if (height < 0) height = 0;
        }

        int y_start = (SCREEN_HEIGHT - height) / 2;
        int y_end = y_start + height;

        for (int y = 0; y < SCREEN_HEIGHT; ++y) {
            if (y >= y_start && y < y_end) {
                if (x < SCREEN_WIDTH / 2) {
                    buffer[y * SCREEN_WIDTH + x] = color_left;
                } else {
                    buffer[y * SCREEN_WIDTH + x] = color_right;
                }
            } else {
                buffer[y * SCREEN_WIDTH + x] = 0x808080;
            }
        }
    }

    int rect_width = 92;
    int rect_height = 69;
    uint32_t rect_color = 0x00000000;

    int color_position = position + FRONTAL_WALL;
    int depth = 0;
    while (color_position < 8 * 8 && data[color_position] == 0 || data[color_position] == 99) {
        color_position = color_position + FRONTAL_WALL;
        depth++;
    }

    if (color_position < 8 * 8) {
        switch (data[color_position]) {
            case 0: 
                rect_color = 0x00000000;
                break;
            case 1: 
                rect_color = 0xB22222;
                break;
            case 2: 
                rect_color = 0xFFFF0000;
                break;
            case 3:
                rect_color = 0x0000FFFF;
                break;
            case 4: 
                rect_color = 0x00FFF00F;
                break;
            default:
                break;
        }
    }

    float ratio = (float)rect_width / rect_height;
    
    // scaling based on depth (nearer means larger)
    float scale_factor = 1.0f - (depth * 0.1f); // size reduced 10% for each level of depth
    scale_factor = scale_factor < 0.3f ? 0.3f : scale_factor; // don't let rect get too small

    rect_width = int(SCREEN_WIDTH * 0.80f * scale_factor); // max width = 80%
    rect_height = int(rect_width / ratio);

    int center_x_rect = SCREEN_WIDTH / 2 - rect_width / 2;
    int center_y_rect = SCREEN_HEIGHT / 2 - rect_height / 2;

    for (int i = center_x_rect; i < center_x_rect + rect_width; ++i) {
        for (int j = center_y_rect; j < center_y_rect + rect_height; ++j) {
            buffer[j * SCREEN_WIDTH + i] = rect_color;
        }
    }
}


void __r_init__()
{
    __m__window = SDL_CreateWindow("ultrared", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    __m__renderer = SDL_CreateRenderer(__m__window, -1, SDL_RENDERER_ACCELERATED);
    
    __m__surface = SDL_GetWindowSurface(__m__window);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetRenderDrawColor(__m__renderer, 0, 0, 0, 0);

    __log("init done.", 0);
}

void __r_loop__(DATA data)
{

    SDL_Event event;

    __m__texture = SDL_CreateTexture(__m__renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    set_visible(data.map_data, buffer, data.position);

    while (true)
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT) {
            __r_quit__();
        }

        // check inputs
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_w:  // move forward
                    if (data.position + FORW > 64) {
                        data.position = data.position;
                    }
                    else if (data.map_data[data.position + FORW] == 0 || data.map_data[data.position + FORW] == 99) {
                        data.position += FORW;
                    }
                    else {
                        data.position = data.position;
                    }
                    set_visible(data.map_data, buffer, data.position);
                    break;

                case SDLK_s:  // move back
                    if (data.position - BACK < 0) {
                        data.position = data.position;
                    }
                    else if (data.map_data[data.position - FORW] == 0 || data.map_data[data.position - FORW] == 99) {
                        data.position -= BACK;
                    }
                    else {
                        data.position = data.position;
                    }

                    set_visible(data.map_data, buffer, data.position);
                    break;

                case SDLK_d:  // move right
                    if (data.position - RIGHT < 0)
                        data.position = data.position;

                    else if (data.map_data[data.position - RIGHT] == 0 || data.map_data[data.position - RIGHT] == 99) {
                        data.position -= RIGHT;
                    }
                    else {
                        data.position = data.position;
                    }
                    set_visible(data.map_data, buffer, data.position);
                    break;

                case SDLK_a:  // move left
                    if (data.position + LEFT > 64) {
                        data.position = data.position;
                    }
                    else if (data.map_data[data.position + LEFT] == 0 || data.map_data[data.position + LEFT] == 99) {
                        data.position += LEFT;
                    }
                    else {
                        data.position = data.position;
                    }
                    set_visible(data.map_data, buffer, data.position);
                    break;

                case SDLK_e: // rotate by +90 deg.
                    if (data.heading+1 > 4) {
                        data.heading = 1;
                    }
                    else {
                        data.heading++;
                    }
                    set_visible(data.map_data, buffer, data.position);
                    break;
                
                case SDLK_q: // rotate by -90 deg.
                    if (data.heading-1 < 1) {
                        data.heading = 4;
                    }
                    else {
                        data.heading--;
                    }
                    set_visible(data.map_data, buffer, data.position);
                    break;

                default:
                    break;
            }

            if (data.heading == 1)// north
            {
                FRONTAL_WALL = -8;
                LEFT_WALL = -1;
                RIGHT_WALL = -1;

                LEFT = -1;
                RIGHT = -1;
                FORW = -8;
                BACK = -8;

                set_visible(data.map_data, buffer, data.position);
            }
            else if (data.heading == 2) // east
            {
                FRONTAL_WALL = +1;
                LEFT_WALL = +8;
                RIGHT_WALL = +8;
                
                LEFT = 8;
                RIGHT = 8;
                FORW = 1;
                BACK = 1;
                
                set_visible(data.map_data, buffer, data.position);
            }
            else if (data.heading == 3) // south
            {
                FRONTAL_WALL = +8;
                LEFT_WALL = +1;
                RIGHT_WALL = +1;

                LEFT = 1;
                RIGHT = 1;
                FORW = 8;
                BACK = 8;

                set_visible(data.map_data, buffer, data.position);
            }
            else if (data.heading == 4) // west
            {
                FRONTAL_WALL = -1;
                LEFT_WALL = 8;
                RIGHT_WALL = 8;

                LEFT = 8;
                RIGHT = 8;
                FORW = -1;
                BACK = -1;

                set_visible(data.map_data, buffer, data.position);
            }
            else
            {
                FRONTAL_WALL = +8;
                LEFT_WALL = +1;
                RIGHT_WALL = +1;

                LEFT = 1;
                RIGHT = 1;
                FORW = 8;
                BACK = 8;

                set_visible(data.map_data, buffer, data.position);
            }

            printf("[UR] POS: %d | HED: %d\n", data.position, data.heading);
            set_visible(data.map_data, buffer, data.position);
        }

        if (data.map_data[data.position] == 99)
            _ui_end_level_screen(__m__window, __m__renderer,
                                 __m__surface, __m__texture);

        // draw shit
        SDL_Delay(10);

        SDL_UpdateTexture(__m__texture, NULL, buffer, SCREEN_WIDTH * 4);

        SDL_RenderCopyEx(
            __m__renderer,
            __m__texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_HORIZONTAL
        );

        SDL_SetRenderDrawColor(__m__renderer, 0, 0, 0, 0);

        SDL_RenderPresent(__m__renderer);
    }

}

int __r_quit__()
{
    __log("shutdown started", 0);
    SDL_DestroyWindow(__m__window);
    SDL_DestroyRenderer(__m__renderer);
    SDL_Quit();
    __log("shutdown finished, exiting.", 0);
    exit(0);
}
