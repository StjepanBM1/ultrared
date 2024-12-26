
// GLOBAL HEADERs
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// LOCAL HEADERs
#include "io/log.hpp"
#include "renderer/renderer.hpp"
#include "file/file.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 2)
        __log("no map file input.", 1);

    __log("loading map file...", 0);

    std::string map_file = argv[1];

    DATA data;

    load_map_file(map_file, data.map_data, data.position, data.heading);

    __r_init__();

    __r_loop__(data);

    __r_quit__();

}
