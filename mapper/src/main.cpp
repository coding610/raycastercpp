#include <raylib.h>
#include "defines.hpp"
#include "grid.hpp"
#include "select.hpp"
#include "ui.hpp"

int main() {
    InitWindow(1000, 1000, "mapper");
    SetTargetFPS(60);

    float fsize = 50; Vector2 cellsize;
    Grid* grid = new Grid();
    Select* select = new Select(grid);
    grid->remake_grid(fsize);

    Color current_color = WHITE;
    while (!WindowShouldClose()) {
        cellsize = grid->get_cellsize();

        select->clear();
        select->multi_select(cellsize);
        select->single_select(cellsize, current_color);
        select->scroll_select(cellsize);
        grid->remake_grid(fsize);
        UI(grid, select, current_color, fsize);

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

        EndDrawing();
    }

    delete grid;
    delete select;
}
