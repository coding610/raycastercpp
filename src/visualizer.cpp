#include "visualizer.hpp"
#include "raymanager.hpp"
#include "utils.hpp"
#include <cmath>
#include <raylib.h>


void Visualizer::draw() const {
    for (int i = 0; i < _rays.size(); i++) {
        DrawRectangle(
            GetRenderWidth() - (i+1) * (GetRenderWidth() / _rays.size()),
            0,
            std::ceil(GetRenderWidth() / _rays.size()),
            GetRenderHeight(),
            Color(
                _rays[i]->_end_color.r,
                _rays[i]->_end_color.g,
                _rays[i]->_end_color.b,
                255 - (255 * (_rays[i]->_length / _raymanager->_MAX_REY_LENGTH))
            )
        );
    }
}

Visualizer::Visualizer(Grid* g, RayManager* r) : _raymanager(r), _grid(g) {
    _rays = _raymanager->_rays;
}
