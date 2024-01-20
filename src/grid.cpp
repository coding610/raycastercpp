#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "grid.hpp"
#include "utils.hpp"


void Grid::draw_lines() {
    // Assuming that grid has the same width and height
    for (int i = 0; i <= grid.size(); i++) {
        DrawLine(
            i * (float) GetRenderWidth() / (grid.size()),
            0,
            i * (float) GetRenderWidth() / (grid.size()),
            (float) GetRenderHeight(),
            Color(200, 200, 255, 30)
        );

        DrawLine(
            0,
            i * (float) GetRenderHeight() / (grid.size()),
            (float) GetRenderWidth(),
            i * (float) GetRenderHeight() / (grid.size()),
            Color(200, 200, 255, 30)
        );
    }
}

void Grid::read_file(const char* path) {
    std::fstream f(path, std::ios::in);
    if (!f) {
        std::cerr << "Error: file \"" << path << "\" not found in function Grid::read_file(const char* path)\n";
        std::exit(1);
    }

    grid = {};
    std::string slice;
    while (std::getline(f, slice)) {
        std::vector<Object> new_slice;
        std::vector<int> data = {0, 0};
        int dataindex = 0;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') {
                new_slice.push_back({ .TYPE = data[0], .HEIGHT = data[1] });
                data = {0, 0}; dataindex = 0;
            } else if (slice[j] == '_') {
                dataindex++;
            } else {
                data[dataindex] = (10 * data[dataindex]) + (slice[j] - '0');
            }
        }

        grid.push_back(new_slice);
    }

    f.close();
}

void Grid::draw_objects() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].TYPE == 0) continue;
            DrawRectangle(
                j * (float) GetRenderWidth() / (grid.size()),
                i * (float) GetRenderHeight() / (grid.size()),
                (float) GetRenderWidth() / (grid.size()),
                (float) GetRenderHeight() / (grid.size()),
                _object_colors[grid[i][j].TYPE]
            );
        }
    }
}
