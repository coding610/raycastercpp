#include "visualizer.hpp"
#include "raymanager.hpp"
#include "utils.hpp"
#include <cmath>
#include <raylib.h>


void Visualizer::draw() const {
    for (int i = 1; i <= _rays.size(); i++) {
        DrawRectangle(
            GetRenderWidth() - i * (GetRenderWidth() / _rays.size()),
            0,
            std::ceil(GetRenderWidth() / _rays.size()),
            GetRenderHeight(),
            Color(
                255 - (255 * (_rays[i-1]->_length / _raymanager->_MAX_REY_LENGTH)),
                255 - (255 * (_rays[i-1]->_length / _raymanager->_MAX_REY_LENGTH)),
                255 - (255 * (_rays[i-1]->_length / _raymanager->_MAX_REY_LENGTH)),
                255
            )
        );
    }
}

Visualizer::Visualizer(Grid* g, RayManager* r) : _raymanager(r), _grid(g) {
    _rays = _raymanager->_rays;
}
