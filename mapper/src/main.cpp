#include <exception>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#define RAYGUI_IMPLEMENTATION
#include <raygui.hpp>

void draw_grid(std::vector<std::vector<int>> grid) {
    std::vector<Color> colors = {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE
    };

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) continue;
            DrawRectangle(
                j * GetRenderWidth() / (grid.size()) + 100,
                i * GetRenderHeight() / (grid.size()) + 100,
                GetRenderWidth() / (grid.size()),
                GetRenderHeight() / (grid.size()),
                colors[grid[i][j]]
            );
        }
    }
}

void remake_grid(std::vector<std::vector<int>>& grid, Vector2& cellsize, float fsize) {
    if ((int) fsize == grid.size()) return;

    cellsize = {
        (float) 1000.0 / (int) fsize,
        (float) 1000.0 / (int) fsize
    };

    int bsize = grid.size();
    auto bgrid = grid;
    grid = {};
    int size = (int) fsize;
    for (int i = 0; i < size; i++) {
        std::vector<int> jj;
        for (int j = 0; j < size; j++) {
            if (i < bsize && j < bsize) {
                jj.push_back(bgrid[i][j]);
            } else {
                jj.push_back(0);
            }
        }
        grid.push_back(jj);
    }
}

void clear_grid(std::vector<std::vector<int>>& grid) {
    auto bgrid = grid;
    grid = {};
    for (int i = 0; i < bgrid.size(); i++) {
        std::vector<int> jj;
        for (int j = 0; j < bgrid.size(); j++) {
            jj.push_back(0);
        }
        grid.push_back(jj);
    }
}

void write_grid(std::vector<std::vector<int>>& grid) {
    std::ofstream f("output.txt", std::ios::out | std::ios::trunc);
    if (!f) {
        std::cerr << "File \"output.txt\" Not Found at function write_grid()\n";
        std::exit(1);
    }

    for (auto& slice : grid) {
        for (auto& num : slice) {
            f << num << " ";
        }
        f << "\n";
    }
    f.close();
}

void read_saved_grid(std::vector<std::vector<int>>& grid, const char* path) {
    std::fstream f(path, std::ios::in);
    if (!f) {
        std::cerr << "Error: file \"" << path << "\" not found in function Grid::read_file(const char* path)\n";
        std::exit(1);
    }

    grid = {};
    std::string slice;
    while (std::getline(f, slice)) {
        std::vector<int> gslice;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') continue;
            int num = slice[j] - 48;
            gslice.push_back(num);
        }
        grid.push_back(gslice);
    }

    f.close();
}

void draw_lines(std::vector<std::vector<int>>& grid) {
    for (int i = 0; i <= grid.size(); i++) {
        DrawLine(
            100 + i * GetRenderWidth() / (grid.size()),
            100,
            100 + i * GetRenderWidth() / (grid.size()),
            GetRenderHeight(),
            Color(200, 200, 255, 50)
        );
        DrawLine(
            100,
            100 + i * GetRenderHeight() / (grid.size()),
            GetRenderWidth(),
            100 + i * GetRenderHeight() / (grid.size()),
            Color(200, 200, 255, 50)
        );
    }
}

int main() {
    InitWindow(1000, 1000, "mapper");
    SetTargetFPS(60);

    float fsize = 50;
    Vector2 cellsize; std::vector<std::vector<int>> grid;
    remake_grid(grid, cellsize, fsize);

    int current_material = 1;
    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetMousePosition();
            if (mousepos.x > 101 && mousepos.y > 101) {
                mousepos.x -= 100; mousepos.y -= 100;
                Vector2 cell = { 
                    std::floor(mousepos.x / cellsize.x),
                    std::floor(mousepos.y / cellsize.y)
                };
                grid[cell.y][cell.x] = current_material;
            }
        }

        remake_grid(grid, cellsize, fsize);
        GuiSlider( Rectangle(200, 40, 700, 20), "10", "100", &fsize, 10, 100 );

        if (GuiButton(Rectangle(10, 200, 80, 80), "0")) {
            current_material = 0;
        } else if (GuiButton(Rectangle(10, 310, 80, 80), "1")) {
            current_material = 1;
        } else if (GuiButton(Rectangle(10, 420, 80, 80), "2")) {
            current_material = 2;
        } else if (GuiButton(Rectangle(10, 530, 80, 80), "3")) {
            current_material = 3;
        } else if (GuiButton(Rectangle(10, 640, 80, 80), "4")) {
            current_material = 4;
        } else if (GuiButton(Rectangle(10, 10, 80, 80), "CLEAR")) {
            clear_grid(grid);
        } else if (GuiButton(Rectangle(10, 820, 80, 80), "WRITE")) {
            write_grid(grid);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(
                100, 100,
                1000 - 100, 1000 - 100,
                Color(10, 10, 10, 255)
            );
            draw_lines(grid);
            draw_grid(grid);
        EndDrawing();
    }
}
