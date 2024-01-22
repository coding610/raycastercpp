#pragma once

#include <optional>
#include <raylib.h>
#include "grid.hpp"
#include "menu.hpp"


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
    Menu* _menu;

    Vector2 _position = {50, 50};
    Vector2 _rotation = {PI, (float) GetRenderHeight() / 2};

    // Constants
    float _radius;
    float _speed;
    const Color _color = WHITE;
    const Color _outline_color = BLACK;
    const Vector3 _MOVEMENT_ACC = {0.2, 0.01, 0.2}; // x -> forward, y -> up and down, z -> strafing
    const Vector2 _SENSITIVITY = {0.1, 100};

public:
    inline Player(Grid* grid, Menu* menu) : _grid(grid), _menu(menu) {
        _radius = ((float) GetRenderWidth() / _grid->grid.size()) / 4;
        _speed = ((float) GetRenderWidth() * _grid->grid.size()) / 150;
    }

    void update(float delta);
    void draw();
    Face inside(Vector2 pos, Vector2 size);

    inline Vector2 get_position() {
        return _position;
    } inline float get_rotation() {
        return _rotation.x;
    } inline float get_rotationy() {
        return _rotation.y;
    }
};
