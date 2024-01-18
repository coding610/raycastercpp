#pragma once

#include <raylib.h>
#include <vector>


class Grid {
private:
    const Vector2 _resolution;
    const std::vector<Color> _object_colors {
        BLACK, // NONE OBJECT
        WHITE,
        RED,
        GREEN,
        BLUE
    };

public:
    std::vector<std::vector<int>> grid = {
        {2, 2, 2, 2, 2, 2, 2, 0},
        {2, 0, 4, 0, 0, 0, 4, 0},
        {2, 0, 4, 4, 0, 4, 0, 0},
        {2, 0, 0, 4, 0, 4, 0, 4},
        {2, 0, 2, 2, 0, 4, 0, 0},
        {2, 0, 0, 0, 0, 2, 4, 0},
        {2, 2, 2, 0, 2, 2, 0, 0},
        {0, 0, 0, 0, 2, 0, 4, 4}
    };

    inline Grid(Vector2 res) : _resolution(res) {};
    void draw_lines();
    void draw_objects();
    void read_file(const char* filename);

    inline Vector2 get_resolution() {
        return _resolution;
    } inline std::vector<Color> get_colors() {
        return _object_colors;
    }
};
