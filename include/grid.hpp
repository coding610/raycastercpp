#pragma once

#include <raylib.h>
#include <vector>

enum class BlockType {
    EMPTY = 0,
    BLOCK = 1,
};

struct Object {
    BlockType type;
    Color color;
    int height;
};


class Grid {
public:
    std::vector<std::vector<Object>> grid = {};

    inline Grid() {};
    void draw_lines();
    void draw_objects();
    void read_file(const char* filename);
};
