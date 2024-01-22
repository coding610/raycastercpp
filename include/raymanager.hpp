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

    Vector2 _end_position;
    Color _end_color = DARKGRAY;
    float _length;
    float _height;


    ////// CONSTANTS //////
    const float _UNIT_HEIGHT = GetRenderHeight() / 10.0;
    const float _MAX_DEPTH = 60;
    float _MAX_RAY_LENGTH;

    ////// DEBUGGING //////
    float _c = 2;
    float _d = 2;

public:
    int _ray_collide = 0;

    _Ray(Grid* g, Player* p, Vector2 cl);
    void cast(
        Grid* grid,
        Vector2 originpos,
        float rotation,
        float originangle,
        Vector2 cellsize,
        int clr_before
    );
    void draw(int i, int size) const;
    inline Vector2 get_position() {
        return _end_position;
    }
};


class RayManager {
private:
    Grid* _grid;
    Player* _player;

    const int _ray_resolution = 1000;
    const float _fov = PI / 4;
    Vector2 _cellsize;
    bool _debug = false;
    bool* _gamemode;

public:
    std::vector<_Ray*> _rays;

    RayManager(Player* pl, Grid* grd, bool* gamemode);
    void update();
    void debug_draw();
};
