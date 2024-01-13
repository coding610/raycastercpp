#include <raylib.h>
#include <chrono>
#include "player.hpp"
#include "visualizer.hpp"
#include "grid.hpp"


int main() {
    const float ratio = 1.0;
    const int height = 800;
    const Vector2 resolution {height * ratio, height};

    InitWindow(resolution.x, resolution.y, "Raycaster");
    SetTargetFPS(60);

    Grid* grid = new Grid(resolution);
    Player* player = new Player(grid, resolution);
    // Visualizer3D* vizualizer3D = new Visualizer(grid, resolution);

    float delta = 0;
    while (!WindowShouldClose()) {
        auto delta1 = std::chrono::steady_clock::now();
        player->update(delta);

        BeginDrawing();
            ClearBackground(BLACK);

            grid->draw_objects();
            grid->draw_lines();
            player->draw();
        EndDrawing();

        auto delta2 = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(delta2 - delta1).count() / 1000.0;
    }


    delete grid;
    // delete visualizer3D;
    delete player;
}
