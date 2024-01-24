#include <raylib.h>
#include <chrono>
#include "player.hpp"
#include "raymanager.hpp"
#include "grid.hpp"
#include "utils.hpp"
#include "menu.hpp"


int main() {
    const float ratio = 1.0;
    const int height = 1000;
    const Vector2 resolution {height * ratio, height};

    InitWindow(resolution.x, resolution.y, "Raycaster");
    SetTargetFPS(60);

    float delta = 0;
    bool gamemode = 0; // 0 for 2d, 1 for 3d

    Menu* menu = new Menu();
    Grid* grid = new Grid(); grid->read_file("mapper/output.txt");
    Player* player = new Player(grid, menu, &gamemode);
    RayManager* rays = new RayManager(player, grid, &gamemode);

    while (!WindowShouldClose()) {
        auto delta1 = std::chrono::steady_clock::now();

        if (IsKeyPressed(KEY_ENTER)) gamemode = !gamemode;
        player->update(delta);
        menu->update();

        BeginDrawing();
            ClearBackground(Color(7, 7, 10));

            rays->update();
            if (gamemode == 0) {
                grid->draw_objects();
                grid->draw_lines();
                player->draw();
                rays->debug_draw();
            }

            DrawFPS(10, 10);
        EndDrawing();

        auto delta2 = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(delta2 - delta1).count() / 1000.0;
    }


    delete grid;
    delete player;
}
