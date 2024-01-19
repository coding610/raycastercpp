#include "visualizer.hpp"
#include "raymanager.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <cmath>
#include <raylib.h>


void Visualizer::draw() const {
    _Ray* ray;
    float wall_height;
    for (int i = 0; i < _rays.size(); i++) {
        ray = _rays[i];
        wall_height = ray->_height * TICK_HEIGHT * GetRenderHeight() / ray->_length;
        if (wall_height > GetRenderHeight()) wall_height = GetRenderHeight();

        DrawLine(
            GetRenderWidth() - (i+1) * (GetRenderWidth() / _rays.size()),
            _player->get_height() - wall_height / 2,
            GetRenderWidth() - (i+1) * (GetRenderWidth() / _rays.size()),
            _player->get_height() + wall_height / 2 + wall_height,
            Color(
                ray->_end_color.r,
                ray->_end_color.g,
                ray->_end_color.b,
                255
            )
        );
    }
}

Visualizer::Visualizer(Grid* g, RayManager* r, Player* p) : _raymanager(r), _grid(g), _player(p) {
    _rays = _raymanager->_rays;
}
