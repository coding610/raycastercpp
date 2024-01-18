#include <cmath>
#include <raylib.h>
#include "player.hpp"
#include "grid.hpp"
#include "raymanager.hpp"
#include "utils.hpp"


void _Ray::cast(Grid* grid, Vector2 originpos, float rotation, Vector2 cellsize) {
    ////// PREREQUISITS //////
    _end_color = YELLOW;
    Vector2 vertical_pos = { originpos.x, utils::cellpos(originpos, cellsize, 0).y };
    Vector2 horizontal_pos = { utils::cellpos(originpos, cellsize, 1).x, originpos.y };
    Vector2 vertical_step = utils::step(vertical_pos, 0, rotation, cellsize);
    Vector2 horizontal_step = utils::step(horizontal_pos, 1, rotation, cellsize);
    
    ////// RAYCAST //////
    int depth = 0;
    bool adjusted_face = false;
    bool face_vertical = false; bool face_horizontal = false;
    bool collide_vertical = false; bool collide_horizontal = false;
    while ((!collide_vertical || !collide_horizontal) && depth < _MAX_DEPTH) { depth++;
        if (!collide_vertical) if (utils::collide(grid, vertical_pos, cellsize, 0, face_vertical)) collide_vertical = true;
        if (!collide_horizontal) if (utils::collide(grid, horizontal_pos, cellsize, 1, face_horizontal)) collide_horizontal = true;

        if (!collide_vertical) { vertical_pos.x += vertical_step.x; vertical_pos.y += vertical_step.y; }
        if (!collide_horizontal) { horizontal_pos.x += horizontal_step.x; horizontal_pos.y += horizontal_step.y; }
    }

    ////// SELECTING RAYTYPE //////
    if (vertical_pos.y < 0 || vertical_pos.y > grid->get_resolution().y) {
        _end_position = horizontal_pos;
    } else if (horizontal_pos.x < 0 || horizontal_pos.x > grid->get_resolution().x) {
        _end_position = vertical_pos;
    } else {
        if (utils::distance(originpos, vertical_pos) >= utils::distance(originpos, horizontal_pos)) {
            _end_position = horizontal_pos;
        } else {
            _end_position = vertical_pos;
        }
    }

    ////// COLOR //////
    Vector2 cell = utils::cell(_end_position, cellsize, true);
    if (utils::inside_field(grid, cell)) {
        _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y]];

        if (_end_position.x == vertical_pos.x && _end_position.y == vertical_pos.y
            && collide_vertical && utils::is_black(_end_color)
        ) {
            _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y - 1]];
        } else if (
            _end_position.x == horizontal_pos.x && _end_position.y == horizontal_pos.y
            && collide_horizontal && utils::is_black(_end_color)
        ) {
            _end_color = grid->get_colors()[grid->grid[(int) cell.x - 1][(int) cell.y]];
        }
    }

    ////// LENGTH //////
    _length = utils::distance(originpos, _end_position);
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
        DrawLineV(_player->get_position(), ray->_end_position, ray->_end_color);
    }
}

RayManager::RayManager(Player* pl, Grid* grd, Vector2 res)
           : _player(pl), _grid(grd), _resolution(res),
           _cellsize({ res.x / grd->grid.size(), res.y / grd->grid[0].size() })
{
    for (int i = 0; i < _number_of_rays; i++) {
        _rays.push_back(new _Ray);
    }
}
