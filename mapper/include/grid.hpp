#pragma once

#include <algorithm>
#include <raylib.h>
#include <vector>
#include <fstream>

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
private:
    std::vector<std::vector<std::vector<Object>>> _grid_history;
    int _grid_index;
    Vector2 _cellsize;

public:
    std::vector<std::vector<Object>> _grid; // TODO: change this to grid because public

    void draw_grid() const;
    void clear_grid();
    void remake_grid(float fsize);
    void draw_lines() const;
    void grid_border(Color color, BlockType type);
    void write_grid() const;
    void read_saved_grid();
    void select_grid(
        std::pair<Vector2,
        Vector2>& selected_cells,
        Color color,
        BlockType type,
        Vector3 preserve = {false, false, false}
    );
    void select_height_grid(std::pair<Vector2, Vector2>& selected_cells, int scroll);
    void undo();
    void redo();
    inline void history() {
        _grid_history.push_back(_grid);
        _grid_index++;
    } inline Vector2 get_cellsize() {
        return _cellsize;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << (int) c.r << "-" << (int) c.g << "-" << (int) c.b << "-" << (int) c.a;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const BlockType& t) {
    switch (t) {
        case BlockType::EMPTY: os << "empty"; break;
        case BlockType::BLOCK: os << "block"; break;
        default: break;
    }

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Object& o) {
    if (o.type == BlockType::EMPTY) {
        os << "B-empty_C-0-0-0-0_H-0";
    } else {
        os << "B-" << o.type << "_C-" << o.color << "_H-" << o.height;
    }
    return os;
}
