#include <raylib.h>
#include <cmath>
#include "select.hpp"
#include "defines.hpp"

void Select::multi_select(Vector2 cellsize) {
    if (IsKeyDown(KEY_LEFT_CONTROL)) return;

    Vector2 mousepos = GetMousePosition();
    if (mousepos.x > SETTING_SIZE + 1 && mousepos.y > SETTING_SIZE + 1) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _currently_selecting = true;
            Vector2 cell = { 
                std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
            };
            _selected_cells.first = cell;
        } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && _currently_selecting) {
            Vector2 cell = { 
                std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
            };
            _selected_cells.second = cell;
        } if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && _currently_selecting) {
            _currently_selecting = false;
            _finished_selecting = true;
        }
    }
}

void Select::single_select(Vector2 cellsize, Color current_color) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mousepos = GetMousePosition();
        if (mousepos.x > 101 && mousepos.y > 101) {
            _finished_selecting = false; _selected_cells = {{0, 0}, {0, 0}};
            _grid->history();
            Vector2 cell = { 
                std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
            };
            _grid->_grid[cell.y][cell.x].color = current_color;
        }
    }
}

void Select::scroll_select(Vector2 cellsize) {
    if (IsKeyDown(KEY_LEFT_CONTROL)) return;

    if (GetMouseWheelMove() != 0) {
        Vector2 mousepos = GetMousePosition();
        if (mousepos.x > SETTING_SIZE + 1 && mousepos.y > SETTING_SIZE + 1) {
            if (_finished_selecting) {
                _grid->select_height_grid(_selected_cells, GetMouseWheelMove());
            } else {
                _grid->history();
                Vector2 cell = { 
                    std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                    std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
                };
                _grid->_grid[cell.y][cell.x].height += GetMouseWheelMove(); // 10 is one block height
                if (_grid->_grid[cell.y][cell.x].height < 0) {
                    _grid->_grid[cell.y][cell.x].height = 0;
                }
            }
        }
    }
}

void Select::draw(Vector2 cellsize) {
    if (_selected_cells.second.x != 0) {
        DrawRectangleRec(
            Rectangle (
                SETTING_SIZE + _selected_cells.first.x * cellsize.x,
                SETTING_SIZE + _selected_cells.first.y * cellsize.y,
                (_selected_cells.second.x - _selected_cells.first.x) * cellsize.x + cellsize.x,
                (_selected_cells.second.y - _selected_cells.first.y) * cellsize.y + cellsize.y
            ),
            Color(0, 0, 255, 50)
        ); DrawRectangleLinesEx(
            Rectangle (
                SETTING_SIZE + _selected_cells.first.x * cellsize.x,
                SETTING_SIZE + _selected_cells.first.y * cellsize.y,
                (_selected_cells.second.x - _selected_cells.first.x) * cellsize.x + cellsize.x,
                (_selected_cells.second.y - _selected_cells.first.y) * cellsize.y + cellsize.y
            ),
            3,
            BLUE
        );
    }
}

void Select::clear() {
    if (IsKeyDown(KEY_BACKSPACE)) {
        _currently_selecting = false;
        _finished_selecting = false;
        _selected_cells = {{0, 0}, {0, 0}};
    }
}

void Select::d_clear() {
    _currently_selecting = false;
    _finished_selecting = false;
    _selected_cells = {{0, 0}, {0, 0}};
}
