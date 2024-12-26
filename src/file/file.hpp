
#ifndef FILE_HPP
#define FILE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

#include "../io/log.hpp"

void load_map_file(std::string &file_path, uint8_t map_data[8 * 8], int &position, int &heading);

#endif // !FILE_HPP
