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
    float _height;
    const float _MAX_DEPTH = 10;

    void cast(Grid* grid, Vector2 originpos, float rotation, float fov, Vector2 cellsize, const float MAX_RAY_LENGTH);
    void draw();
};


class RayManager {
private:
    Grid* _grid;
    Player* _player;
    const Vector2 _resolution;

    const int _ray_resolution = 1000;
    const float _fov = PI / 4;
    const Vector2 _cellsize;

public:
    int _MAX_RAY_LENGTH;
    std::vector<_Ray*> _rays;

    RayManager(Player* pl, Grid* grd, Vector2 res);
    void update();
    void draw();
};
