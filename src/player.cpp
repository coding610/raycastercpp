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
    utils::adjust_radians(_rotation);

    ////// ACCELERATION //////
    float forwards_velocity = 0;
    float im_rotation = _rotation;
    float rot_acc = 2; float forw_acc = 3;

    ////// MOVEMENT //////
    if (IsKeyDown(KEY_LEFT_CONTROL)) forw_acc = 1;
    if (IsKeyDown(KEY_LEFT_SHIFT)) forw_acc = 5;
    if (IsKeyDown(KEY_LEFT))  im_rotation += rot_acc * delta;
    if (IsKeyDown(KEY_RIGHT)) im_rotation -= rot_acc * delta;
    if (IsKeyDown(KEY_W)) forwards_velocity += forw_acc;
    if (IsKeyDown(KEY_S)) forwards_velocity -= forw_acc;
    if (IsKeyDown(KEY_A)) { im_rotation += PI/2; forwards_velocity += forw_acc; }
    if (IsKeyDown(KEY_D)) { im_rotation -= PI/2; forwards_velocity += forw_acc; }

    ////// NEUTRALIZE STRAFING //////
    if (forwards_velocity > forw_acc) forwards_velocity = forw_acc;
    else if (forwards_velocity < -forw_acc) forwards_velocity = -forw_acc;

    ////// 3D VIEW ANGLE //////
    if (IsKeyDown(KEY_UP)) _height += 1000 * delta;
    if (IsKeyDown(KEY_DOWN)) _height -= 1000 * delta;

    ////// MOVE PLAYER //////
    _position.x += std::sin(im_rotation - PI) * forwards_velocity * _speed * delta;
    _position.y += std::cos(im_rotation - PI) * forwards_velocity * _speed * delta;
    
    ////// COLLISION WITH OBJECTS //////
    for (int i = 0; i < _grid->grid.size(); i++) {
        for (int j = 0; j < _grid->grid[i].size(); j++) {
            if (_grid->grid[i][j].TYPE == 0) continue;

            Face face = inside(
                {j * _resolution.x / (_grid->grid.size()),
                i * _resolution.y / (_grid->grid.size())},
                {_resolution.x / (_grid->grid.size()),
                _resolution.y / (_grid->grid.size())}
            );

            if (face == Face::UP || face == Face::DOWN) {
                _position.y -= std::cos(im_rotation - PI) * forwards_velocity * _speed * delta;
            } else if (face == Face::LEFT || face == Face::RIGHT) {
                _position.x -= std::sin(im_rotation - PI) * forwards_velocity * _speed * delta;
            }
        }
    }

    ////// REVERSE STRAFING //////
    if (IsKeyDown(KEY_A)) im_rotation -= PI/2;
    if (IsKeyDown(KEY_D)) im_rotation += PI/2;

    ////// SET _ROTATION //////
    _rotation = im_rotation;
}

Face Player::inside(Vector2 pos, Vector2 size) {
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
        for (auto &f : faces)
        distances.push_back(utils::distance(_position, f));
        int min_index = std::distance(
        std::begin(distances),
        std::min_element(std::begin(distances), std::end(distances)));

        return Face(min_index);
    }

    return Face::NONE;
}

void Player::draw() {
    DrawCircleV(_position, _radius, _color);
    DrawRing(_position, _radius - 3, _radius, 0, 360, 3000, _outline_color);
}
