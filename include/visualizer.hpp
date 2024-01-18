#pragma once

#include "raymanager.hpp"


class Visualizer {
private:
    RayManager* _raymanager;
    std::vector<_Ray*> _rays;
    Grid* _grid;

public:
    Visualizer(Grid* grid, RayManager* r);
    void draw() const;
};
