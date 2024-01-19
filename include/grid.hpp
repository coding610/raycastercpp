#pragma once

#include <raylib.h>
#include <vector>

struct Object {
    int TYPE;
    float HEIGHT;
};


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
    std::vector<std::vector<Object>> grid = {};

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
