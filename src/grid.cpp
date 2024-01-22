#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "grid.hpp"
#include "utils.hpp"


void Grid::draw_lines() {
    // Assuming that grid has the same width and height
    for (int i = 0; i <= grid.size(); i++) {
        DrawLine(
            i * (float) GetRenderWidth() / (grid.size()),
            0,
            i * (float) GetRenderWidth() / (grid.size()),
            (float) GetRenderHeight(),
            Color(200, 200, 255, 30)
        );

        DrawLine(
            0,
            i * (float) GetRenderHeight() / (grid.size()),
            (float) GetRenderWidth(),
            i * (float) GetRenderHeight() / (grid.size()),
            Color(200, 200, 255, 30)
        );
    }
}

void Grid::read_file(const char* path) {
    std::fstream f(path, std::ios::in);
    if (!f) {
        std::cerr << "Error: file \"" << path << "\" not found in function Grid::read_saved_grid)\n";
        std::exit(1);
    }

    grid = {};
    std::string slice;
    while (std::getline(f, slice)) {
        std::vector<Object> new_slice;
        BlockType datat;
        Color datac;
        int datah;
        for (int j = 0; j < slice.length(); j++) {
            if (slice[j] == ' ') {
                new_slice.push_back({.type = datat, .color = datac, .height = datah});
            } else if (slice[j] == 'B') {
                j += 2;
                std::string keyword = "";
                while (std::isalpha(slice[j])) {
                    keyword.push_back(slice[j]);
                    j++;
                }
                if (keyword == "empty") datat = BlockType::EMPTY;
                else if (keyword == "block") datat = BlockType::BLOCK;

                j--;
             } else if (slice[j] == 'C') {
                 j += 2;
                 int clr;
                 for (int i = 0; i < 4; i++) {
                     clr = 0;
                     while (std::isdigit(slice[j])) {
                         clr = 10 * clr + (slice[j] - '0');
                         j++;
                     }
                     switch (i) {
                         case 0: datac.r = clr;
                         case 1: datac.g = clr;
                         case 2: datac.b = clr;
                         case 3: datac.a = clr;
                     }
                     
                     j++;
                 }

                 j--;
             } else if (slice[j] == 'H') {
                 j += 2;
                 int r = 0;
                 while (std::isdigit(slice[j])) {
                     r = 10 * r + (slice[j] - '0');
                     j++;
                 }

                 datah = r;
                 j--;
             }

        }

        grid.push_back(new_slice);
    }

    f.close();
}

void Grid::draw_objects() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j].type == BlockType::EMPTY) continue;
            DrawRectangle(
                j * (float) GetRenderWidth() / (grid.size()),
                i * (float) GetRenderHeight() / (grid.size()),
                (float) GetRenderWidth() / (grid.size()),
                (float) GetRenderHeight() / (grid.size()),
                grid[i][j].color
            );
        }
    }
}
