#include <cmath>
#include <raylib.h>
#include "player.hpp"
#include "grid.hpp"
#include "raymanager.hpp"
#include "utils.hpp"


void _Ray::cast(
    Grid* grid,
    Vector2 originpos,
    float angle,
    float originangle,
    Vector2 cellsize,
    int clr_before
) {
    ////// PREREQUISITS //////
    _end_color = BLACK;
    Vector2 vertical_pos = { originpos.x, utils::cellpos(originpos, cellsize, 0).y };
    Vector2 horizontal_pos = { utils::cellpos(originpos, cellsize, 1).x, originpos.y };
    Vector2 vertical_step = utils::step(vertical_pos, 0, angle, cellsize);
    Vector2 horizontal_step = utils::step(horizontal_pos, 1, angle, cellsize);
    
    ////// RAYCAST //////
    int depth = 0;
    bool face_vertical = false; bool face_horizontal = false;
    bool collide_vertical = false; bool collide_horizontal = false;
    int collide_first = -1; // 0 for vert, 1 for hori
    while ((!collide_vertical || !collide_horizontal) && depth < _MAX_DEPTH) { depth++;
        if (!collide_vertical) if (utils::collide(grid, vertical_pos, cellsize, 0, face_vertical)) collide_vertical = true;
        if (!collide_horizontal) if (utils::collide(grid, horizontal_pos, cellsize, 1, face_horizontal)) collide_horizontal = true;

        if (!collide_vertical) { vertical_pos.x += vertical_step.x; vertical_pos.y += vertical_step.y; }
        if (!collide_horizontal) { horizontal_pos.x += horizontal_step.x; horizontal_pos.y += horizontal_step.y; }
    }

    ////// SELECTING RAY //////
    if (utils::distance(originpos, vertical_pos) > utils::distance(originpos, horizontal_pos)) {
        _end_position = horizontal_pos;
        _ray_collide = 1;
    } else if (utils::distance(originpos, vertical_pos) < utils::distance(originpos, horizontal_pos)) {
        _end_position = vertical_pos;
        _ray_collide = 0;
    } else { // TODO: FIX COLOR WHEN SAME, clr before?
        _end_position = vertical_pos;
        _ray_collide = clr_before;
    }

    ////// COLOR //////
    Vector2 cell = utils::cell(_end_position, cellsize, true);
    if (utils::inside_field(grid, cell)) {
        _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y].TYPE];
        _height = grid->grid[(int) cell.x][(int) cell.y].HEIGHT;

        if (_end_position.x == vertical_pos.x && _end_position.y == vertical_pos.y && collide_vertical && utils::is_black(_end_color)) {
            _end_color = grid->get_colors()[grid->grid[(int) cell.x][(int) cell.y - 1].TYPE];
            _height = grid->grid[(int) cell.x][(int) cell.y - 1].HEIGHT;
        } else if (_end_position.x == horizontal_pos.x && _end_position.y == horizontal_pos.y && collide_horizontal && utils::is_black(_end_color)) {
            _end_color = grid->get_colors()[grid->grid[(int) cell.x - 1][(int) cell.y].TYPE];
            _height = grid->grid[(int) cell.x - 1][(int) cell.y].HEIGHT;
        }
    }

    ////// FISH-EYE ADJUSTMENTS //////
    float delta_radians = originangle - angle; utils::adjust_radians(delta_radians);
    _length = utils::distance(originpos, _end_position) * std::cos(delta_radians);
}

void RayManager::update() {
    if (IsKeyPressed(KEY_BACKSPACE)) _debug = !_debug;

    for (int i = 0; i < _rays.size(); i++) {
        float rot = _player->get_rotation() + i * (_fov / _rays.size()) - (_fov / 2);
        utils::adjust_radians(rot);

        int clr;
        if (i == 0) clr = 0;
        else clr = _rays[i-1]->_ray_collide;
        _rays[i]->cast(_grid, _player->get_position(), rot, _player->get_rotation(), _cellsize, clr);
        if (*_gamemode == 1) _rays[i]->draw(i, _rays.size());
    }
}

void RayManager::debug_draw() {
    if (*_gamemode == 1 || !_debug) return;
    for (auto& ray : _rays) {
        DrawLineV(_player->get_position(), ray->get_position(), Color(200, 200, 50, 100));
    }
}

RayManager::RayManager(Player* pl, Grid* grd, bool* gm)
           : _player(pl), _grid(grd),
           _cellsize({ (float) GetRenderWidth() / grd->grid.size(), (float) GetRenderHeight() / grd->grid[0].size() }),
           _gamemode(gm)
{
    for (int i = 0; i < _ray_resolution; i++) {
        _rays.push_back(new _Ray(_grid, _player, _cellsize));
    }
}

_Ray::_Ray(Grid* g, Player* p, Vector2 cl) : _grid(g), _player(p), _cellsize(cl) {
    _MAX_RAY_LENGTH = _MAX_DEPTH * ((float) GetRenderWidth() / (float) _grid->grid.size());
}
