#include <charconv>
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
    int HEIGHT;
};

template<typename T>
void DEB(T mess) {
    std::cout << mess << "\n";
}

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
            Rectangle r = Rectangle (
                j * cellsize.x + SETTING_SIZE,
                i * cellsize.y + SETTING_SIZE,
                cellsize.x,
                cellsize.y
            );
            DrawRectangle(r.x, r.y, r.width, r.height, colors[grid[i][j].TYPE]);
            GuiDrawText(
                std::to_string(grid[i][j].HEIGHT).substr(0, 3).c_str(),
                r,
                TEXT_ALIGN_MIDDLE,
                BLACK
            );
        }
    }
}

void remake_grid(std::vector<std::vector<Object>>& grid, std::vector<std::vector<std::vector<Object>>>& grid_history, Vector2& cellsize, float fsize, int& gridindex) {
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

    grid_history.push_back(grid); gridindex++;
}

void clear_grid(std::vector<std::vector<Object>>& grid, std::vector<std::vector<std::vector<Object>>>& grid_history, int& gridindex) {
    auto bgrid = grid;
    grid = {};
    for (int i = 0; i < bgrid.size(); i++) {
        std::vector<Object> jj;
        for (int j = 0; j < bgrid.size(); j++) {
            jj.push_back({.TYPE = 0, .HEIGHT = 1});
        }
        grid.push_back(jj);
    }

    grid_history.push_back(grid);
    gridindex++;
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
        std::vector<Object> new_slice;
        std::vector<int> data = {0, 0};
        int dataindex = 0;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') {
                new_slice.push_back({ .TYPE = data[0], .HEIGHT = data[1] });
                data = {0, 0}; dataindex = 0;
            } else if (slice[j] == '_') {
                dataindex++;
            } else {
                data[dataindex] = (10 * data[dataindex]) + (slice[j] - '0');
            }
        }

        grid.push_back(new_slice);
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

void select_grid(
    std::vector<std::vector<Object>>& grid,
    std::vector<std::vector<std::vector<Object>>>& grid_history,
    int& gridindex,
    std::pair<Vector2, Vector2>& selectcell,
    int type
) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (((j >= selectcell.first.x && j <= selectcell.second.x) || (j <= selectcell.first.x && j >= selectcell.second.x))
                && ((i >= selectcell.first.y && i <= selectcell.second.y) || (i <= selectcell.first.y && i >= selectcell.second.y))) {
                grid[i][j].TYPE = type;
            }
        }
    }

    grid_history.push_back(grid); gridindex++;
    selectcell = {{0, 0}, {0, 0}};
}

void undo(std::vector<std::vector<Object>>& grid, std::vector<std::vector<std::vector<Object>>> grid_history, int& gridindex) {
    gridindex--;
    grid = grid_history[gridindex];
}

void redo(std::vector<std::vector<Object>>& grid, std::vector<std::vector<std::vector<Object>>> grid_history, int& gridindex) {
    gridindex++;
    grid = grid_history[gridindex];
}


int main() {
    InitWindow(1000, 1000, "mapper");
    SetTargetFPS(60);

    float fsize = 50;
    Vector2 cellsize;
    int gridindex = 0;
    std::vector<std::vector<Object>> grid;
    std::vector<std::vector<std::vector<Object>>> grid_history;
    remake_grid(grid, grid_history, cellsize, fsize, gridindex);

    bool selecting = false;
    bool selected_area = false;
    std::pair<Vector2, Vector2> selectcell = {{0, 0}, {0, 0}};

    int current_type = 1;
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_BACKSPACE)) {
            selecting = false;
            selected_area = false;
            selectcell = {{0, 0}, {0, 0}};
        }
        if (!IsKeyDown(KEY_LEFT_CONTROL)) {
            Vector2 mousepos = GetMousePosition();
            if (mousepos.x > 101 && mousepos.y > 101) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    selecting = true;
                    Vector2 cell = { 
                        std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                        std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
                    };
                    selectcell.first = cell;
                } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selecting) {
                    Vector2 cell = { 
                        std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                        std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
                    };
                    selectcell.second = cell;
                } if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selecting) {
                    selecting = false;
                    selected_area = true;
                }
            }
        } if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousepos = GetMousePosition();
            if (mousepos.x > 101 && mousepos.y > 101) {
                selected_area = false; selectcell = {{0, 0}, {0, 0}};
                grid_history.push_back(grid); gridindex++;
                Vector2 cell = { 
                    std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                    std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
                };
                grid[cell.y][cell.x].TYPE = current_type;
            }
        } else if (GetMouseWheelMove() != 0) {
            Vector2 mousepos = GetMousePosition();
            if (mousepos.x > 101 && mousepos.y > 101) {
                grid_history.push_back(grid); gridindex++;
                Vector2 cell = { 
                    std::floor((mousepos.x - SETTING_SIZE) / cellsize.x),
                    std::floor((mousepos.y - SETTING_SIZE) / cellsize.y)
                };
                grid[cell.y][cell.x].HEIGHT += GetMouseWheelMove(); // 10 is one block height
                if (grid[cell.y][cell.x].HEIGHT < 0) {
                    grid[cell.y][cell.x].HEIGHT = 0;
                }
            }
        }

        remake_grid(grid, grid_history, cellsize, fsize, gridindex);

        GuiSlider( Rectangle(200, 40, 700, 20), "10", "100", &fsize, 10, 100 );
        if (GuiButton(Rectangle(10, 10, 80, 80), "CLEAR")) {
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, 0); selected_area = false; }
            else clear_grid(grid, grid_history, gridindex);
        } if (GuiButton(Rectangle(10, 110, 80, 80), "0")) {
            current_type = 0;
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, current_type); selected_area = false; }
        } if (GuiButton(Rectangle(10, 210, 80, 80), "1")) {
            current_type = 1;
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, current_type); selected_area = false; }
        } if (GuiButton(Rectangle(10, 310, 80, 80), "2")) {
            current_type = 2;
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, current_type); selected_area = false; }
        } if (GuiButton(Rectangle(10, 410, 80, 80), "3")) {
            current_type = 3;
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, current_type); selected_area = false; }
        } if (GuiButton(Rectangle(10, 510, 80, 80), "4")) {
            current_type = 4;
            if (selected_area) { select_grid(grid, grid_history, gridindex, selectcell, current_type); selected_area = false; }
        } if (GuiButton(Rectangle(10, 610, 80, 80), "BORDER")) {
            grid_border(grid, current_type);
        } if (GuiButton(Rectangle(10, 710, 80, 80), "WRITE")) {
            write_grid(grid);
        } if (GuiButton(Rectangle(10, 810, 80, 80), "READ")) {
            read_saved_grid(grid, SAVEDPATH);
        } if (GuiButton(Rectangle(10, 910, 80, 35), "UNDO")) {
            undo(grid, grid_history, gridindex);
        } if (GuiButton(Rectangle(10, 955, 80, 35), "REDO")) {
            redo(grid, grid_history, gridindex);
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

            if (selectcell.second.x != 0) {
                DrawRectangleRec(
                    Rectangle (
                        SETTING_SIZE + selectcell.first.x * cellsize.x,
                        SETTING_SIZE + selectcell.first.y * cellsize.y,
                        (selectcell.second.x - selectcell.first.x) * cellsize.x + cellsize.x,
                        (selectcell.second.y - selectcell.first.y) * cellsize.y + cellsize.y
                    ),
                    Color(0, 0, 255, 50)
                ); DrawRectangleLinesEx(
                    Rectangle (
                        SETTING_SIZE + selectcell.first.x * cellsize.x,
                        SETTING_SIZE + selectcell.first.y * cellsize.y,
                        (selectcell.second.x - selectcell.first.x) * cellsize.x + cellsize.x,
                        (selectcell.second.y - selectcell.first.y) * cellsize.y + cellsize.y
                    ),
                    3,
                    BLUE
                );
            }

        EndDrawing();
    }
}
