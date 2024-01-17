#pragma once

#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "grid.hpp"

class _Ray {
public:
    Vector2 _end_position;
    float _length;
    const float _MAX_DEPTH = 5;

    void cast(Grid* grid, Vector2 originpos, float rotation, Vector2 cellsize);
};


class RayManager {
private:
    Grid* _grid;
    Player* _player;
    std::vector<_Ray*> _rays;
    const Vector2 _resolution;

    const int _number_of_rays = 500;
    const float _fov = 1.1; // In radians
    Vector2 _cellsize;

public:
    RayManager(Player* pl, Grid* grd, Vector2 res);
    void update();
    void draw();
};
