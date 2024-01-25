#pragma once

#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "grid.hpp"
#include "ray.hpp"


class RayStepper {
private:
    Grid* _grid;
    Player* _player;

    const int _ray_resolution = GetRenderWidth();
    const float _fov = PI / 4;
    Vector2 _cellsize;
    bool _debug = false;
    bool* _gamemode;

public:
    std::vector<_Ray*> _rays;

    RayStepper(Player* pl, Grid* grd, bool* gamemode);
    void update();
    void debug_draw();
};
