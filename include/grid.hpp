#pragma once

#include <raylib.h>
#include <vector>


class Grid {
private:
    const Vector2 _resolution;
    const Color _object_colors[5] { BLACK, WHITE, RED, GREEN, BLUE };

public:
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    inline Grid(Vector2 res) : _resolution(res) {};
    void draw_lines();
    void draw_objects();
    inline Vector2 get_resolution() {
        return _resolution;
    }
};
