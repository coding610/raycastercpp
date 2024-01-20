#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>


template<typename T>
inline void DEB(T mess) {
    std::cout << mess << "\n";
}

namespace utils {
inline bool compare_color(Color c1, Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

inline int color_to_int(std::vector<Color> colors, Color c) {
    for (int i = 0; i < colors.size(); i++) {
        if (utils::compare_color(colors[i], c)) {
            return i;
        }
    }

    return -1;
}

};
