#pragma once

#include <raylib.h>
#include <vector>
#include "grid.hpp"

class Select {
private:
    Grid* _grid;
    bool _currently_selecting = false;

public:
    bool _finished_selecting = false;
    std::pair<Vector2, Vector2> _selected_cells = {{0, 0}, {0, 0}};

    inline Select(Grid* grid) : _grid(grid) {}

    void clear();
    void d_clear();
    void multi_select(Vector2 cellsize);
    void single_select(Vector2 cellsize, Color current_color);
    void scroll_select(Vector2 cellsize);
    void draw(Vector2 cellsize);
};
