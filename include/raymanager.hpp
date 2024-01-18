#pragma once

#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "grid.hpp"

class _Ray {
public:
    Vector2 _end_position;
    Color _end_color = DARKGRAY;
    float _length;
    const float _MAX_DEPTH = 3;

    void cast(Grid* grid, Vector2 originpos, float rotation, Vector2 cellsize);
};


class RayManager {
private:
    Grid* _grid;
    Player* _player;
    const Vector2 _resolution;

    const int _ray_resolution = 800;
    const float _fov = PI / 2;
    const Vector2 _cellsize;

public:
    int _MAX_REY_LENGTH;
    std::vector<_Ray*> _rays;

    RayManager(Player* pl, Grid* grd, Vector2 res);
    void update();
    void draw();
};
