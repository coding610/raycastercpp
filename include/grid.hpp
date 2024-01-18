#pragma once

#include <raylib.h>
#include <vector>


class Grid {
private:
    const Vector2 _resolution;
    const std::vector<Color> _object_colors {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE
    };

public:
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 2, 2, 2, 0},
        {0, 0, 0, 2, 0, 0, 0, 0},
        {0, 2, 2, 0, 0, 4, 4, 0},
        {0, 0, 2, 4, 4, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 3, 0},
        {0, 1, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 3, 3, 0}
    };

    inline Grid(Vector2 res) : _resolution(res) {};
    void draw_lines();
    void draw_objects();

    inline Vector2 get_resolution() {
        return _resolution;
    } inline std::vector<Color> get_colors() {
        return _object_colors;
    }
};
