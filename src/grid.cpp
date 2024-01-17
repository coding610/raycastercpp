#include <raylib.h>
#include <iostream>
#include "grid.hpp"


void Grid::draw_lines() {
    // Assuming that grid has the same width and height
    for (int i = 0; i <= grid.size(); i++) {
        // DrawLine(
        //     i * _resolution.x / (grid.size()),
        //     0,
        //     i * _resolution.x / (grid.size()),
        //     _resolution.y,
        //     WHITE
        // );

        DrawLine(
            0,
            i * _resolution.y / (grid.size()),
            _resolution.x,
            i * _resolution.y / (grid.size()),
            WHITE
        );
    }
}

void Grid::draw_objects() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
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
