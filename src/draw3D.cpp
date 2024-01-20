#include "raymanager.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <raylib.h>
#include <cmath>


void _Ray::draw(int i, int size) const {
    float wall_height = _UNIT_HEIGHT * GetRenderHeight() / _length;

    // Draw wall
    DrawLine(
        GetRenderWidth() - (i+1) * (GetRenderWidth() / size),
        _player->get_rotationy() - (wall_height / 2) * (_height / 10),
        GetRenderWidth() - (i+1) * (GetRenderWidth() / size),
        _player->get_rotationy() + (wall_height / 2),
        Color(
            _end_color.r,
            _end_color.g,
            _end_color.b,
            25500 * _ray_collide + 25500
        )
    );
}
