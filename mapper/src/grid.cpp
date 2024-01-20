#include <raylib.h>
#include <fstream>
#include "grid.hpp"
#include "defines.hpp"
#include "utils.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.hpp>

void Grid::draw_grid() const {
    for (int i = 0; i < _grid.size(); i++) {
        for (int j = 0; j < _grid[i].size(); j++) {
            Rectangle r = Rectangle (
                j * _cellsize.x + SETTING_SIZE,
                i * _cellsize.y + SETTING_SIZE,
                _cellsize.x,
                _cellsize.y
            );
            DrawRectangle(r.x, r.y, r.width, r.height, _grid[i][j].color);
            GuiDrawText(
                std::to_string(_grid[i][j].height).substr(0, 3).c_str(),
                r,
                TEXT_ALIGN_MIDDLE,
                BLACK
            );
        }
    }
}

void Grid::draw_lines() const {
    for (int i = 0; i <= _grid.size(); i++) {
        DrawLine(
            SETTING_SIZE + i * _cellsize.x,
            SETTING_SIZE,
            SETTING_SIZE + i * _cellsize.x,
            GetRenderHeight(),
            Color(200, 200, 255, 50)
        );
        DrawLine(
            SETTING_SIZE,
            SETTING_SIZE + i * _cellsize.y,
            GetRenderWidth(),
            SETTING_SIZE + i * _cellsize.y,
            Color(200, 200, 255, 50)
        );
    }
}

void Grid::remake_grid(float fsize) {
    if ((int) fsize == _grid.size()) return;

    _cellsize = {
        ((float) GetRenderWidth() - SETTING_SIZE) / (int) fsize,
        ((float) GetRenderHeight() - SETTING_SIZE) / (int) fsize
    };

    int bsize = _grid.size();
    auto bgrid = _grid;
    _grid = {};
    int size = (int) fsize;
    for (int i = 0; i < size; i++) {
        std::vector<Object> jj;
        for (int j = 0; j < size; j++) {
            if (i < bsize && j < bsize) {
                jj.push_back(bgrid[i][j]);
            } else {
                jj.push_back({.type = BlockType::EMPTY});
            }
        }
        _grid.push_back(jj);
    }

    history();
}

void Grid::clear_grid() {
    auto bgrid = _grid;
    _grid = {};
    for (int i = 0; i < bgrid.size(); i++) {
        std::vector<Object> jj;
        for (int j = 0; j < bgrid.size(); j++) {
            jj.push_back({.type = BlockType::EMPTY});
        }
        _grid.push_back(jj);
    }

    history();
}

void Grid::grid_border(Color color) {
    for (int i = 0; i < _grid.size(); i++) {
        for (int j = 0; j < _grid[i].size(); j++) {
            if (i == 0 || i + 1 == _grid.size() || j == 0 || j + 1 == _grid[i].size()) {
                _grid[i][j].color = color;
            }
        }
    }
}

void Grid::write_grid() const {
    std::ofstream f("output.txt", std::ios::out | std::ios::trunc);
    if (!f) {
        std::cerr << "File \"output.txt\" Not Found at function write_grid()\n";
        std::exit(1);
    }

    for (auto& slice : _grid) {
        for (auto& o : slice) {
            f << o << " ";
        }
        f << "\n";
    }
    f.close();
}
void Grid::read_saved_grid() { } // TODO

void Grid::select_grid( std::pair<Vector2, Vector2>& selectcell, Color color) {
    for (int i = 0; i < _grid.size(); i++) {
        for (int j = 0; j < _grid[0].size(); j++) {
            if (((j >= selectcell.first.x && j <= selectcell.second.x) || (j <= selectcell.first.x && j >= selectcell.second.x))
                && ((i >= selectcell.first.y && i <= selectcell.second.y) || (i <= selectcell.first.y && i >= selectcell.second.y))) {
                _grid[i][j].color = color;
            }
        }
    }

    _grid_history.push_back(_grid); _grid_index++;
    selectcell = {{0, 0}, {0, 0}};
}

void Grid::select_height_grid(std::pair<Vector2, Vector2>& selectcell, int scroll) {
    for (int i = 0; i < _grid.size(); i++) {
        for (int j = 0; j < _grid[0].size(); j++) {
            if (((j >= selectcell.first.x && j <= selectcell.second.x) || (j <= selectcell.first.x && j >= selectcell.second.x))
                && ((i >= selectcell.first.y && i <= selectcell.second.y) || (i <= selectcell.first.y && i >= selectcell.second.y))) {
                _grid[i][j].height += scroll;
                if (_grid[i][j].height < 0) {
                    _grid[i][j].height = 0;
                }
            }
        }
    }

    _grid_history.push_back(_grid); _grid_index++;
}

void Grid::undo() {
    _grid_index--;
    _grid = _grid_history[_grid_index];
}

void Grid::redo() {
    _grid_index++;
    _grid = _grid_history[_grid_index];
}
