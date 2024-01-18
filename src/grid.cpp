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
            i * _resolution.x / (grid.size()),
            0,
            i * _resolution.x / (grid.size()),
            _resolution.y,
            Color(200, 200, 255, 30)
        );

        DrawLine(
            0,
            i * _resolution.y / (grid.size()),
            _resolution.x,
            i * _resolution.y / (grid.size()),
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
        std::vector<int> gslice;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') continue;
            int num = slice[j] - 48;
            gslice.push_back(num);
        }
        grid.push_back(gslice);
    }

    f.close();
}

void Grid::draw_objects() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) continue;
            DrawRectangle(
                j * _resolution.x / (grid.size()),
                i * _resolution.y / (grid.size()),
                _resolution.x / (grid.size()),
                _resolution.y / (grid.size()),
                _object_colors[grid[i][j]]
            );
        }
    }
}
