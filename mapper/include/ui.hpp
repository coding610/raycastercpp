#pragma once

#include <raylib.h>
#include "select.hpp"
#include "grid.hpp"
#include "defines.hpp"
#include <iostream>

// Its already defined in grid
// #define RAYGUI_IMPLEMENTATION
#include <raygui.hpp>

inline void UI(Grid* grid, Select* select, Color& current_color, float& fsize) {
    GuiSlider( Rectangle(200, 40, 700, 20), "10", "100", &fsize, 10, 100 );
    if (GuiButton(Rectangle(10, 10, 80, 80), "CLEAR")) {
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, WHITE); select->d_clear(); } // FIXME
        else grid->clear_grid();
    } if (GuiButton(Rectangle(10, 110, 80, 80), "WHITE")) {
        current_color = WHITE;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 210, 80, 80), "RED")) {
        current_color = RED;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 310, 80, 80), "GREEN")) {
        current_color = GREEN;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 410, 80, 80), "BLUE")) {
        current_color = BLUE;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 510, 80, 80), "CUSTOM")) {
        current_color = WHITE;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 610, 80, 80), "BORDER")) {
        grid->grid_border(current_color);
    } if (GuiButton(Rectangle(10, 710, 80, 80), "WRITE")) {
        grid->write_grid();
    } if (GuiButton(Rectangle(10, 810, 80, 80), "READ")) {
        grid->read_saved_grid();
    } if (GuiButton(Rectangle(10, 910, 80, 35), "UNDO")) {
        grid->undo();
    } if (GuiButton(Rectangle(10, 955, 80, 35), "REDO")) {
        grid->redo();
    }
}
