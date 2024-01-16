#pragma once


#include <cmath>
#include <iostream>
#include <raylib.h>
#include "player.hpp"

template<typename T>
inline void DEB(T mes) {
    std::cout << mes << "\n";
}

template<typename T>
inline void DBN(T mes) {
    std::cout << mes;
}


inline void DEB(Vector2 mes) {
    DEB(mes.x);
    DEB(mes.y);
}


namespace utils {

inline int square(int num) {
    return num*num;
}

inline float distance(Vector2 p1, Vector2 p2) {
    return std::sqrt(
        square(std::abs(p1.x - p2.x)) +
        square(std::abs(p1.y - p2.y))
    );
}

inline Vector2 cell(Vector2 pos, Vector2 cellsize, bool transform = false) {
    if (transform) {
        return {
            std::floor(pos.y / cellsize.y),
            std::floor(pos.x / cellsize.x)
        };
    } else {
        return {
            std::floor(pos.x / cellsize.x),
            std::floor(pos.y / cellsize.y)
        };
    }
}

inline Vector2 cellpos(Vector2 pos, Vector2 cellsize, int xy = -1) {
    if (xy == 0) {
        return {
            cellsize.x * std::floor(pos.x / cellsize.x),
            pos.y
        };
    } else if (xy == 1) {
        return {
            pos.x,
            cellsize.y * std::floor(pos.y / cellsize.y)
        };
    } else {
        return {
            cellsize.x * std::floor(pos.x / cellsize.x),
            cellsize.y * std::floor(pos.y / cellsize.y)
        };
    }
}

inline float get_step(Vector2 pos, bool aligment, float rotation, Vector2 cellsize, bool relative) {
    if (relative) {
        if (aligment == 0) {
            if (rotation < PI) {
                return cellsize.x - std::abs(pos.x - utils::cellpos(pos, cellsize, 0).x);
            } else {
                return -std::abs(pos.x - utils::cellpos(pos, cellsize).x);
            }
        } else { // FIXME
            if (rotation > PI / 2 && rotation < 1.5 * PI) return -cellsize.y;
            else return cellsize.y;
        }
    } else {
        if (aligment == 0) {
            if (rotation < PI) return cellsize.y;
            else return -cellsize.y;
        } else {
            if (rotation > PI / 2 && rotation < 1.5 * PI) return -cellsize.y;
            else return cellsize.y;
        }
    }
}

inline Vector2 step(Vector2& pos, bool aligment, float rotation, Vector2 cellsize) {
    float relative_step = utils::get_step(pos, aligment, rotation, cellsize, true);
    float fixed_step = utils::get_step(pos, aligment, rotation, cellsize, false);

    if (aligment == 0) {
        pos.x += relative_step;
        pos.y += relative_step / std::tan(rotation);
        return {
            fixed_step,
            fixed_step / std::tan(rotation)
        };
    } else {
        pos.x += relative_step * std::tan(rotation);
        pos.y += relative_step;
        return {
            fixed_step * std::tan(rotation),
            fixed_step
        };
    }
}

inline void adjust_radians(float& rad) {
    if (rad < 0) rad = 2 * PI + rad;
    else if (rad > 2 * PI) rad = rad - 2 * PI;
}

inline bool collide(Grid* grid, Vector2 pos, Vector2 cellsize) {
    Vector2 cell = utils::cell(pos, cellsize, true);
    if (cell.x > 0 && cell.y > 0 &&
        cell.x < grid->grid.size() && cell.y < grid->grid[0].size()
    ) {
        if (grid->grid[cell.x][cell.y]) {
            return true;
        }
    }

    return false;
}

}
