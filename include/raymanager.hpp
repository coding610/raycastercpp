#pragma once

#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "grid.hpp"

class _Ray {
private:
    Grid* _grid;
    Player* _player;
    Vector2 _cellsize;
    const float _UNIT_HEIGHT = GetRenderHeight() / 20.0;

public:
    Vector2 _end_position;
    Color _end_color = DARKGRAY;
    float _length;
    float _height;
    const float _MAX_DEPTH = 10;
    float _MAX_RAY_LENGTH;

    _Ray(Grid* g, Player* p, Vector2 cl);
    void cast(
        Grid* grid,
        Vector2 originpos,
        float rotation,
        float originangle,
        Vector2 cellsize,
        int i,
        int size
    );
    void draw(int i, int size) const;
};


class RayManager {
private:
    Grid* _grid;
    Player* _player;

    const int _ray_resolution = 1000;
    const float _fov = PI / 4;
    const Vector2 _cellsize;

public:
    std::vector<_Ray*> _rays;

    RayManager(Player* pl, Grid* grd);
    void update();
    void draw();
};
