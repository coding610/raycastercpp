#include <raylib.h>
#include "defines.hpp"
#include "grid.hpp"
#include "select.hpp"
#include "ui.hpp"

#include <raygui.hpp>


int main() {
    InitWindow(1000, 1000, "mapper");
    SetTargetFPS(60);

    float fsize = 10; Vector2 cellsize;
    Grid* grid = new Grid();
    Select* select = new Select(grid);
    grid->remake_grid(fsize);

    Color current_color = WHITE;
    Color custom_current_color = Color(255, 0, 255, 100); bool selecting_custom_color = false;
    BlockType current_type = BlockType::BLOCK;
    while (!WindowShouldClose()) {
        cellsize = grid->get_cellsize();

        if (!selecting_custom_color) {
            select->clear();
            select->multi_select(cellsize);
            select->single_select(cellsize, current_color, current_type);
            select->scroll_select(cellsize);
            grid->remake_grid(fsize);
        }
        UI(grid, select, current_color, current_type, fsize, selecting_custom_color, custom_current_color);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(
                100, 100,
                GetRenderWidth() - 100, GetRenderHeight() - 100,
                Color(10, 10, 10, 255)
            );
            grid->draw_lines();
            grid->draw_grid();
            select->draw(cellsize);
            if (selecting_custom_color) {
                GuiColorPicker(
                    Rectangle((float) GetRenderWidth()/2 - 200, (float) GetRenderHeight() / 2 - 200, 400, 400),
                    "charchar",
                    &custom_current_color
                );
            }

            DrawText(
                std::to_string((int) fsize).c_str(),
                105,
                105,
                20,
                WHITE
            );

        EndDrawing();
    }

    delete grid;
    delete select;
}
