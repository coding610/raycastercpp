#pragma once

#include "player.hpp"
#include "raymanager.hpp"


class Visualizer {
private:
    RayManager* _raymanager;
    std::vector<_Ray*> _rays;
    Grid* _grid;
    Player* _player;
    const float TICK_HEIGHT = GetRenderHeight() / 20.0;

public:
    Visualizer(Grid* grid, RayManager* r, Player* p);
    void draw() const;
};
