#include <exception>
#include <raylib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#define RAYGUI_IMPLEMENTATION
#include <raygui.hpp>

#define SETTING_SIZE 100
#define SAVEDPATH "output.txt"

struct Object {
    int TYPE;
    float HEIGHT;
};

void draw_grid(std::vector<std::vector<Object>> grid, Vector2 cellsize) {
    std::vector<Color> colors = {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE
    };

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].TYPE == 0) continue;
            DrawRectangle(
                j * cellsize.x + SETTING_SIZE,
                i * cellsize.y + SETTING_SIZE,
                cellsize.x,
                cellsize.y,
                colors[grid[i][j].TYPE]
            );
        }
    }
}

void remake_grid(std::vector<std::vector<Object>>& grid, Vector2& cellsize, float fsize) {
    if ((int) fsize == grid.size()) return;

    cellsize = {
        ((float) GetRenderWidth() - SETTING_SIZE) / (int) fsize,
        ((float) GetRenderHeight() - SETTING_SIZE) / (int) fsize
    };

    int bsize = grid.size();
    auto bgrid = grid;
    grid = {};
    int size = (int) fsize;
    for (int i = 0; i < size; i++) {
        std::vector<Object> jj;
        for (int j = 0; j < size; j++) {
            if (i < bsize && j < bsize) {
                jj.push_back(bgrid[i][j]);
            } else {
                jj.push_back({.TYPE = 0, .HEIGHT = 1});
            }
        }
        grid.push_back(jj);
    }
}

void clear_grid(std::vector<std::vector<Object>>& grid) {
    auto bgrid = grid;
    grid = {};
    for (int i = 0; i < bgrid.size(); i++) {
        std::vector<Object> jj;
        for (int j = 0; j < bgrid.size(); j++) {
            jj.push_back({.TYPE = 0, .HEIGHT = 1});
        }
        grid.push_back(jj);
    }
}

void write_grid(std::vector<std::vector<Object>>& grid) {
    std::ofstream f("output.txt", std::ios::out | std::ios::trunc);
    if (!f) {
        std::cerr << "File \"output.txt\" Not Found at function write_grid()\n";
        std::exit(1);
    }

    for (auto& slice : grid) {
        for (auto& o : slice) {
            f << o.TYPE << "_" << o.HEIGHT << " ";
        }
        f << "\n";
    }
    f.close();
}

void read_saved_grid(std::vector<std::vector<Object>>& grid, const char* path) {
    std::fstream f(path, std::ios::in);
    if (!f) {
        std::cerr << "Error: file \"" << path << "\" not found in function Grid::read_file(const char* path)\n";
        std::exit(1);
    }

    grid = {};
    std::string slice;
    while (std::getline(f, slice)) {
        std::vector<Object> gslice;
        std::vector<int> data = {0, 0};
        int dataindex = 0;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') {
                gslice.push_back({.TYPE = data[0], .HEIGHT = (float) data[1]});
                data = {0, 0};
                dataindex = 0;
            } else if (slice[j] == '_') {
                dataindex++;
            } else {
                data[dataindex] = slice[j] - 48;
            }
        }

        grid.push_back(gslice);
    }

    f.close();
}

void grid_border(std::vector<std::vector<Object>>& grid, int type) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (i == 0 || i + 1 == grid.size() || j == 0 || j + 1 == grid[i].size()) {
                grid[i][j].TYPE = type;
            }
        }
    }
}

void draw_lines(std::vector<std::vector<Object>>& grid, Vector2 cellsize) {
    for (int i = 0; i <= grid.size(); i++) {
        DrawLine(
            SETTING_SIZE + i * cellsize.x,
            SETTING_SIZE,
            SETTING_SIZE + i * cellsize.x,
            GetRenderHeight(),
            Color(200, 200, 255, 50)
        );
        DrawLine(
            SETTING_SIZE,
            SETTING_SIZE + i * cellsize.y,
            GetRenderWidth(),
            SETTING_SIZE + i * cellsize.y,
            Color(200, 200, 255, 50)
        );
    }
}


int main() {
    InitWindow(1000, 1000, "mapper");
    SetTargetFPS(60);

    float fsize = 50;
    Vector2 cellsize; std::vector<std::vector<Object>> grid;
    remake_grid(grid, cellsize, fsize);

    int current_type = 1;
    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetMousePosition();
            if (mousepos.x > 101 && mousepos.y > 101) {
                mousepos.x -= 100; mousepos.y -= 100;
                Vector2 cell = { 
                    std::floor(mousepos.x / cellsize.x),
                    std::floor(mousepos.y / cellsize.y)
                };
                grid[cell.y][cell.x].TYPE = current_type;
            }
        }

        remake_grid(grid, cellsize, fsize);

        GuiSlider( Rectangle(200, 40, 700, 20), "10", "100", &fsize, 10, 100 );
        if (GuiButton(Rectangle(10, 10, 80, 80), "CLEAR")) {
            clear_grid(grid);
        } else if (GuiButton(Rectangle(10, 110, 80, 80), "0")) {
            current_type = 0;
        } else if (GuiButton(Rectangle(10, 210, 80, 80), "1")) {
            current_type = 1;
        } else if (GuiButton(Rectangle(10, 310, 80, 80), "2")) {
            current_type = 2;
        } else if (GuiButton(Rectangle(10, 410, 80, 80), "3")) {
            current_type = 3;
        } else if (GuiButton(Rectangle(10, 510, 80, 80), "4")) {
            current_type = 4;
        } else if (GuiButton(Rectangle(10, 610, 80, 80), "BORDER")) {
            grid_border(grid, current_type);
        } else if (GuiButton(Rectangle(10, 710, 80, 80), "WRITE")) {
            write_grid(grid);
        } else if (GuiButton(Rectangle(10, 810, 80, 80), "READ")) {
            read_saved_grid(grid, SAVEDPATH);
        } 

        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(
                100, 100,
                GetRenderWidth() - 100, GetRenderHeight() - 100,
                Color(10, 10, 10, 255)
            );
            draw_lines(grid, cellsize);
            draw_grid(grid, cellsize);
        EndDrawing();
    }
}
