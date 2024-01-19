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
    const Vector2 _resolution;
    Grid* _grid;

    Vector2 _position = {150, 150};
    Vector2 _velocity = {0, 0};
    float _rotation = PI;
    float _height = GetRenderHeight() / 2.0;

    // Constants
    float _radius;
    float _speed;
    const Color _color = WHITE;
    const Color _outline_color = BLACK;

public:
    inline Player(Grid* grid, Vector2 res) : _grid(grid), _resolution(res) {
        _radius = ((float) GetRenderWidth() / _grid->grid.size()) / 4;
        _speed = ((float) GetRenderWidth() * _grid->grid.size()) / 150;
    }

    void update(float delta);
    void draw();
    Face inside(Vector2 pos, Vector2 size);

    inline Vector2 get_position() {
        return _position;
    } inline float get_rotation() {
        return _rotation;
    } inline float get_height() {
        return _height;
    }
};
