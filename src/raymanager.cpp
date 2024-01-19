#include <cmath>
#include <raylib.h>
#include "player.hpp"
#include "grid.hpp"
#include "raymanager.hpp"
#include "utils.hpp"


void _Ray::cast(Grid* grid, Vector2 originpos, float rotation, float originangle, Vector2 cellsize, const float MAX_RAY_LENGTH) { // TODO: Change rotation to angle
    ////// PREREQUISITS //////
    _end_color = BLACK;
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

    ////// SELECTING RAY //////
    bool ray_selected; // 0 for vert, 1 for hori
    if (utils::distance(originpos, vertical_pos) >= utils::distance(originpos, horizontal_pos)) {
        ray_selected = 1;
        _end_position = horizontal_pos;
    } else {
        ray_selected = 0;
        _end_position = vertical_pos;
    }

    ////// COLOR //////
    Vector2 cell = utils::cell(_end_position, cellsize, true);
    if (utils::inside_field(grid, cell)) {
        _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y].TYPE];

        if (_end_position.x == vertical_pos.x && _end_position.y == vertical_pos.y && collide_vertical && utils::is_black(_end_color))
            _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y - 1].TYPE];
        else if (_end_position.x == horizontal_pos.x && _end_position.y == horizontal_pos.y && collide_horizontal && utils::is_black(_end_color))
            _end_color = grid->get_colors()[grid->grid[(int) cell.x - 1][(int) cell.y].TYPE];

        _height = grid->grid[(int) cell.x][(int) cell.y].HEIGHT;
    }

    ////// FISH-EYE ADJUSTMENTS //////
    float delta_radians = originangle - rotation; utils::adjust_radians(delta_radians);
    _length = utils::distance(originpos, _end_position) * std::cos(delta_radians);
}

void RayManager::update() {
    for (int i = 0; i < _rays.size(); i++) {
        float rot = _player->get_rotation() + i * (_fov / _rays.size()) - (_fov / 2);
        utils::adjust_radians(rot);

        _rays[i]->cast(_grid, _player->get_position(), rot, _player->get_rotation(), _cellsize, _MAX_RAY_LENGTH);
    }
}

void RayManager::draw() {
    for (auto& ray : _rays) {
        DrawLineV(_player->get_position(), ray->_end_position, YELLOW);
    }
}

RayManager::RayManager(Player* pl, Grid* grd, Vector2 res)
           : _player(pl), _grid(grd), _resolution(res),
           _cellsize({ res.x / grd->grid.size(), res.y / grd->grid[0].size() })
{
    _MAX_RAY_LENGTH = _rays[0]->_MAX_DEPTH * ((float) GetRenderWidth() / (float) _grid->grid.size());
    for (int i = 0; i < _ray_resolution; i++) {
        _rays.push_back(new _Ray(_MAX_RAY_LENGTH));
    }
}
