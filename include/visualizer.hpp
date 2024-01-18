#pragma once

#include "raymanager.hpp"


class Visualizer {
private:
    RayManager* _rays;

public:
    Visualizer(RayManager* r) : _rays(r) {};
    void draw();
};
