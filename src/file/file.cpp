
#include "file.hpp"

void load_map_file(std::string &file_path, uint8_t map_data[8 * 8], int &position, int &heading)
{
    std::ifstream file(file_path);

    if (!file.is_open()) {
        __log("failed to open the map file.", 1);
    }

    std::string line;
    bool reading_map_data = false;
    int row = 0;

    while (std::getline(file, line))
    {
        if (line.find("[MAP DATA]") != std::string::npos) {
            reading_map_data = true; // Start parsing map data
            continue;
        }
        else if (line.find("[POSITION]") != std::string::npos) {
            position = std::stoi(line.substr(line.find(' ') + 1));
        }
        else if (line.find("[HEADING]") != std::string::npos) {
            heading = std::stoi(line.substr(line.find(' ') + 1));
        }

        if (reading_map_data) {
            if (line.empty() || line[0] == '[') {
                break;
            }
            
            std::istringstream iss(line);
            int value;
            int col = 0;

            while (iss >> value) {
                if (row < 8 && col < 8) {
                    map_data[row * 8 + col] = static_cast<uint8_t>(value);
                    col++;
                }
            }

            row++;
        }
    }

    if (!reading_map_data) {
        __log("no [MAP DATA] section found in the map file.", 1);
    }

}
