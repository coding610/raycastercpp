#include "player.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <optional>
#include <raylib.h>
#include "utils.hpp"

void Player::update(float delta) {
    utils::adjust_radians(_rotation.x);

    ////// ACCELERATION //////
    float forwards_velocity = 0;
    float strafing_velocity = 0;
    float rot_acc = _ROTATION_ACC.x;
    float movement_acc = 5;

    ////// MOVEMENT //////
    if (IsKeyDown(KEY_LEFT_SHIFT)) movement_acc = 10;
    if (IsKeyDown(KEY_W)) forwards_velocity += movement_acc * _MOVEMENT_ACC.x;      // +X MOVEMENT
    if (IsKeyDown(KEY_S)) forwards_velocity -= movement_acc * _MOVEMENT_ACC.x;      // -X MOVEMENT
    if (IsKeyDown(KEY_A)) strafing_velocity += movement_acc * _MOVEMENT_ACC.z;      // +Z MOVEMENT
    if (IsKeyDown(KEY_D)) strafing_velocity -= movement_acc * _MOVEMENT_ACC.z;      // -Z MOVEMENT
    if (IsKeyDown(KEY_LEFT))  _rotation.x += rot_acc * delta;                       // +X ROTATION
    if (IsKeyDown(KEY_RIGHT)) _rotation.x -= rot_acc * delta;                       // -X ROTATION
    if (IsKeyDown(KEY_UP)) _rotation.y += _ROTATION_ACC.y * delta;                  // +Y ROTATION
    if (IsKeyDown(KEY_DOWN)) _rotation.y -= _ROTATION_ACC.y * delta;                // -Y ROTATION

    ////// NEUTRALIZE VECTORING //////
    if (strafing_velocity != 0 && forwards_velocity != 0) {
        strafing_velocity /= std::sqrt(2);
        forwards_velocity /= std::sqrt(2);
    }

    ////// MOVE PLAYER //////
    _position.x += std::sin(_rotation.x - PI) * forwards_velocity * _speed * delta;
    _position.y += std::cos(_rotation.x - PI) * forwards_velocity * _speed * delta;
    _position.x += std::sin(_rotation.x - PI + PI / 2) * strafing_velocity * _speed * delta;
    _position.y += std::cos(_rotation.x - PI + PI / 2) * strafing_velocity * _speed * delta;

    ////// COLLISION WITH OBJECTS //////
    for (int i = 0; i < _grid->grid.size(); i++) {
        for (int j = 0; j < _grid->grid[i].size(); j++) {
            if (_grid->grid[i][j].TYPE == 0) continue;

            Face face = inside(
                {j * (float) GetRenderWidth() / (_grid->grid.size()),
                 i * (float) GetRenderHeight() / (_grid->grid.size())},
                {(float) GetRenderWidth() / (_grid->grid.size()),
                 (float) GetRenderHeight() / (_grid->grid.size())}
            );

            if (face == Face::UP || face == Face::DOWN) {
                if (forwards_velocity != 0) _position.y -= std::cos(_rotation.x - PI) * forwards_velocity * _speed * delta;
                if (strafing_velocity != 0) _position.y -= std::cos(_rotation.x - PI + PI / 2) * strafing_velocity * _speed * delta;
            } else if (face == Face::LEFT || face == Face::RIGHT) {
                if (forwards_velocity != 0) _position.x -= std::sin(_rotation.x - PI) * forwards_velocity * _speed * delta;
                if (strafing_velocity != 0) _position.x -= std::sin(_rotation.x - PI + PI / 2) * strafing_velocity * _speed * delta;
            }
        }
    }
}

Face Player::inside(Vector2 pos, Vector2 size) { // TODO: to utils
    if (pos.x < _position.x + _radius && pos.x + size.x > _position.x - _radius &&
        pos.y < _position.y + _radius && pos.y + size.y > _position.y - _radius
    ) {
        // Get nearest face to the point inside
        Vector2 faces[4] = {
            {pos.x, pos.y + size.y / 2},          // Left
            {pos.x + size.x / 2, pos.y},          // Up
            {pos.x + size.x, pos.y + size.y / 2}, // Right
            {pos.x + size.x / 2, pos.y + size.y}, // Up
        };

        std::vector<float> distances;
        for (auto &f : faces) distances.push_back(utils::distance(_position, f));

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
    DrawRing(_position, _radius - 3, _radius, 0, 360, 3000, _outline_color);
}
