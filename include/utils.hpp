#pragma once


#include <cmath>
#include <iostream>
#include <raylib.h>
#include "player.hpp"


namespace utils {

template<typename T>
inline void DEB(T mes) {
    std::cout << mes << "\n";
}

inline int square(int num) {
    return num*num;
}

inline float distance(Vector2 p1, Vector2 p2) {
    return std::sqrt(
        square(std::abs(p1.x - p2.x)) +
        square(std::abs(p1.y - p2.y))
    );
}

}
