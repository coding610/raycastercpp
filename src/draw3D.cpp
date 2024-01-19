#include "raymanager.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <cmath>
#include <raylib.h>


void _Ray::draw(int i, int size) const {
    float wall_height = _height * _UNIT_HEIGHT * GetRenderHeight() / _length;
    if (wall_height > GetRenderHeight()) wall_height = GetRenderHeight();

    DrawLine(
        GetRenderWidth() - (i+1) * (GetRenderWidth() / size),
        _player->get_rotationx() - wall_height / 2,
        GetRenderWidth() - (i+1) * (GetRenderWidth() / size),
        _player->get_rotationx() + wall_height / 2 + wall_height,
        Color(
            _end_color.r,
            _end_color.g,
            _end_color.b,
            255
        )
    );
}
