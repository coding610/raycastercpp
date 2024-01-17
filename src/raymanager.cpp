#include <cmath>
#include <raylib.h>
#include "player.hpp"
#include "grid.hpp"
#include "raymanager.hpp"
#include "utils.hpp"


void _Ray::cast(Grid* grid, Vector2 originpos, float rotation, Vector2 cellsize) {
    Vector2 vertical_pos = {
        originpos.x,
        utils::cellpos(originpos, cellsize, 0).y
    }; Vector2 horizontal_pos = {
        utils::cellpos(originpos, cellsize, 1).x,
        originpos.y
    };
    Vector2 vertical_step = utils::step(vertical_pos, 0, rotation, cellsize);
    Vector2 horizontal_step = utils::step(horizontal_pos, 1, rotation, cellsize);

    ////// VERTICAL //////
    for (int i = 0; i < _MAX_DEPTH; i++) {
        if (utils::collide(grid, vertical_pos, cellsize))
            break;
        vertical_pos.x += vertical_step.x; vertical_pos.y += vertical_step.y;
    }

    ////// HORIZONTAL //////
    for (int i = 0; i < _MAX_DEPTH; i++) {
        if (utils::collide(grid, horizontal_pos, cellsize))
            break;
        horizontal_pos.x += horizontal_step.x; horizontal_pos.y += horizontal_step.y;
    }

    if (utils::distance(originpos, vertical_pos) >= utils::distance(originpos, horizontal_pos)) {
        _end_position = horizontal_pos;
    } else {
        _end_position = vertical_pos;
    }
    _end_position = vertical_pos;
}

void RayManager::update() {
    for (int i = 0; i < _rays.size(); i++) {
        auto ray = _rays[i];
        float rot = _player->get_rotation() + i * (_fov / _rays.size()) - (_fov / 2);
        utils::adjust_radians(rot);

        ray->cast(_grid, _player->get_position(), rot, _cellsize);
    }
}

void RayManager::draw() {
    for (auto& ray : _rays) {
        DrawLineV(_player->get_position(), ray->_end_position, WHITE);
    }

    update();
    std::exit(0);
}

RayManager::RayManager(Player* pl, Grid* grd, Vector2 res) : _player(pl), _grid(grd), _resolution(res) {
    for (int i = 0; i < _number_of_rays; i++) {
        _rays.push_back(new _Ray);
    }

    _cellsize = {
        _resolution.x / _grid->grid.size(),
        _resolution.y / _grid->grid[0].size()
    };
}
