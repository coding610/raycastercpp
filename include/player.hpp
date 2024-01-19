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
    Grid* _grid;

    Vector2 _position = {150, 150};
    Vector2 _rotation = {(float) (GetRenderHeight() / 2.0), PI};

    // Constants
    float _radius;
    float _speed;
    const Color _color = WHITE;
    const Color _outline_color = BLACK;

    const Vector2 _ROTATION_ACC = {1000, 2}; // rotates around the x and y plane
    const Vector2 _MOVEMENT_ACC = {3, 3};

public:
    inline Player(Grid* grid) : _grid(grid) {
        _radius = ((float) GetRenderWidth() / _grid->grid.size()) / 4;
        _speed = ((float) GetRenderWidth() * _grid->grid.size()) / 150;
    }

    void update(float delta);
    void draw();
    Face inside(Vector2 pos, Vector2 size);

    inline Vector2 get_position() {
        return _position;
    } inline float get_rotation() {
        return _rotation.y;
    } inline float get_rotationx() {
        return _rotation.x;
    }
};
