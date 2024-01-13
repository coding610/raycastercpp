#include <algorithm>
#include <raylib.h>
#include <optional>
#include <iostream>
#include <iterator>
#include "utils.hpp"
#include "player.hpp"

using utils::DEB;

void Player::update(float delta) {
    ////// MOVEMENT //////
    _velocity = {0, 0};
    if (IsKeyDown(KEY_LEFT)) {
        _velocity.x += -1;
    } if (IsKeyDown(KEY_RIGHT)) {
        _velocity.x += 1;
    } if (IsKeyDown(KEY_UP)) {
        _velocity.y += -1;
    } if (IsKeyDown(KEY_DOWN)) {
        _velocity.y += 1;
    } 

    _position.x += _velocity.x * _speed * delta;
    _position.y += _velocity.y * _speed * delta;

    for (int i = 0; i < _grid->grid.size(); i++) {
        for (int j = 0; j < _grid->grid[i].size(); j++) {
            if (_grid->grid[i][j] == 0) continue;
            Face face = inside(
                {j * _resolution.x / (_grid->grid.size()),
                i * _resolution.y / (_grid->grid.size())},
                {_resolution.x / (_grid->grid.size()),
                _resolution.y / (_grid->grid.size())}
            );

            if (face == Face::UP || face == Face::DOWN) {
                _position.y -= _velocity.y * _speed * delta;
            } else if (face == Face::LEFT || face == Face::RIGHT) {
                _position.x -= _velocity.x * _speed * delta;
            } 
        }
    }
}

Face Player::inside(Vector2 pos, Vector2 size) {
    if (pos.x < _position.x + _radius && pos.x + size.x > _position.x - _radius
        && pos.y < _position.y + _radius && pos.y + size.y > _position.y - _radius) {

        // Get nearest face to the point inside
        Vector2 faces[4] = {
            {pos.x, pos.y + size.y / 2}, // Left
            {pos.x + size.x / 2, pos.y}, // Up
            {pos.x + size.x, pos.y + size.y / 2}, // Right
            {pos.x + size.x / 2, pos.y + size.y}, // Up
        };

        std::vector<float> distances;
        for (auto& f : faces) distances.push_back(utils::distance(_position, f));
        int min_index = std::distance(
            std::begin(distances),
            std::min_element(std::begin(distances), std::end(distances))
        );

        return Face(min_index);
    }

    return Face::NONE;
}

void Player::draw() {
    DrawCircleV(_position, _radius, _color);
    DrawRing(_position, _radius-3, _radius, 0, 360, 3000, _outline_color);
}
