#pragma once

#include <raylib.h>
#include <vector>

struct Object {
    int TYPE;
    float HEIGHT;
};


class Grid {
private:
    const std::vector<Color> _object_colors {
        BLACK, // NONE OBJECT
        WHITE,
        Color(255, 0, 0, 255),
        GREEN,
        BLUE
    };

public:
    std::vector<std::vector<Object>> grid = {};

    inline Grid() {};
    void draw_lines();
    void draw_objects();
    void read_file(const char* filename);

    inline std::vector<Color> get_colors() {
        return _object_colors;
    }
};
