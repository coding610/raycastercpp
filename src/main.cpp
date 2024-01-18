#include <raylib.h>
#include <chrono>
#include "player.hpp"
#include "visualizer.hpp"
#include "raymanager.hpp"
#include "grid.hpp"
#include "utils.hpp"


int main() {
    const float ratio = 1.0;
    const int height = 800;
    const Vector2 resolution {height * ratio, height};

    InitWindow(resolution.x, resolution.y, "Raycaster");
    SetTargetFPS(60);

    Grid* grid = new Grid(resolution);
    Player* player = new Player(grid, resolution);
    RayManager* rays = new RayManager(player, grid, resolution);
    Visualizer* visualizer = new Visualizer(rays);

    float delta = 0;
    bool gamemode = 0; // 0 for 2d, 1 for 3d
    while (!WindowShouldClose()) {
        auto delta1 = std::chrono::steady_clock::now();

        if (IsKeyPressed(KEY_ENTER)) {
            gamemode = !gamemode;
        }

        player->update(delta);
        rays->update();

        BeginDrawing();
            ClearBackground(BLACK);

            if (gamemode == 0) {
                grid->draw_objects();
                grid->draw_lines();
                player->draw();
                rays->draw();
            } else {
                visualizer->draw();
            }

            DrawFPS(10, 10);
        EndDrawing();

        auto delta2 = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(delta2 - delta1).count() / 1000.0;
    }


    delete grid;
    delete player;
    // delete visualizer3D;
}
