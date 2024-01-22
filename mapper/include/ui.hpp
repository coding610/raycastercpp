#pragma once

#include <raylib.h>
#include "select.hpp"
#include "grid.hpp"
#include "defines.hpp"
#include "utils.hpp"
#include <iostream>

// Its already defined in grid
// #define RAYGUI_IMPLEMENTATION
#include <raygui.hpp>

inline void UI(Grid* grid, Select* select, Color& current_color, BlockType& current_type, float& fsize, bool& selecting_custom_color, Color& custom_current_color) {
    GuiSlider( Rectangle(300, 40, 600, 20), "10", "100", &fsize, 10, 100 );

    if (GuiButton(Rectangle(110, 10, 80, 80), "BLOCK") && !selecting_custom_color) {
        current_type = BlockType::BLOCK;
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color, current_type, {false, true, true}); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 10, 80, 80), "CLEAR") && !selecting_custom_color) {
        if (select->_finished_selecting) { grid->select_grid(select->_selected_cells, current_color, BlockType::EMPTY); select->d_clear(); }
        else grid->clear_grid();
    } if (GuiButton(Rectangle(10, 110, 80, 80), "WHITE") && !selecting_custom_color) {
        if (!select->_finished_selecting) { current_color = WHITE; selecting_custom_color = false; }
        else { grid->select_grid(select->_selected_cells, WHITE, current_type); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 210, 80, 80), "RED") && !selecting_custom_color) {
        if (!select->_finished_selecting) { current_color = RED; selecting_custom_color = false; }
        else { grid->select_grid(select->_selected_cells, RED, current_type); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 310, 80, 80), "GREEN") && !selecting_custom_color) {
        if (!select->_finished_selecting) { current_color = GREEN; selecting_custom_color = false; }
        else { grid->select_grid(select->_selected_cells, GREEN, current_type); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 410, 80, 80), "BLUE") && !selecting_custom_color) {
        if (!select->_finished_selecting) { current_color = BLUE; selecting_custom_color = false; }
        else { grid->select_grid(select->_selected_cells, BLUE, current_type); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 510, 80, 35), "CUSTOM")) {
        if (selecting_custom_color == true) current_color = custom_current_color;
        selecting_custom_color = !selecting_custom_color;
    } if (GuiButton(Rectangle(10, 555, 80, 35), "COLOR") && !selecting_custom_color) {
        if (!select->_finished_selecting) { current_color = custom_current_color; }
        else { grid->select_grid(select->_selected_cells, custom_current_color, current_type); select->d_clear(); }
    } if (GuiButton(Rectangle(10, 610, 80, 80), "BORDER") && !selecting_custom_color) {
        grid->grid_border(current_color, current_type);
    } if (GuiButton(Rectangle(10, 710, 80, 80), "WRITE") && !selecting_custom_color) {
        grid->write_grid();
    } if (GuiButton(Rectangle(10, 810, 80, 80), "READ") && !selecting_custom_color) {
        grid->read_saved_grid();
    } if (GuiButton(Rectangle(10, 910, 80, 35), "UNDO") && !selecting_custom_color) {
        grid->undo();
    } if (GuiButton(Rectangle(10, 955, 80, 35), "REDO") && !selecting_custom_color) {
        grid->redo();
    }

    const Color color_when_selected = Color(200, 30, 30, 100);
    DrawRectangleRec(Rectangle(10, 510, 80, 35), custom_current_color);
    if (current_type == BlockType::BLOCK) {
        DrawRectangleRec(
            Rectangle(110, 10, 80, 80),
            color_when_selected
        );
    } if (utils::compare_color(current_color, custom_current_color)) {
        DrawRectangleRec(
            Rectangle(10, 555, 80, 35),
            color_when_selected
        );
    } else if (utils::compare_color(current_color, WHITE)) {
        DrawRectangleRec(
            Rectangle(10, 110, 80, 80),
            color_when_selected
        );
    } else if (utils::compare_color(current_color, RED)) {
        DrawRectangleRec(
            Rectangle(10, 210, 80, 80),
            color_when_selected
        );
    } else if (utils::compare_color(current_color, GREEN)) {
        DrawRectangleRec(
            Rectangle(10, 310, 80, 80),
            color_when_selected
        );
    } else if (utils::compare_color(current_color, BLUE)) {
        DrawRectangleRec(
            Rectangle(10, 410, 80, 80),
            color_when_selected
        );
    }
}
