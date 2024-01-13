#pragma once

#include <optional>
#include <raylib.h>
#include "grid.hpp"


enum Face {
    LEFT,
    UP,
    RIGHT,
    DOWN,
    NONE
};

class Player {
private:
    // Objects
    Vector2 _position = {600, 300};
    Vector2 _velocity = {0, 0};
    Vector2 _resolution;
    Grid* _grid;

    // Constants
    const float _radius = 13;
    const float _speed = 100;
    const Color _color = WHITE;
    const Color _outline_color = BLACK;

public:
    Player(Grid* grid, Vector2 res) : _grid(grid), _resolution(res) {}
    void update(float delta);
    void draw();
    Face inside(Vector2 pos, Vector2 size);
};
