#include <raylib.h>
#include "menu.hpp"

Menu::Menu() {
    HideCursor();
    playing = true;
}


void Menu::update() {
    if (IsKeyPressed(KEY_TAB)) {
        if (playing) {
            ShowCursor();
        } else {
            HideCursor();
            SetMousePosition(GetRenderWidth() / 2.0, GetRenderHeight() / 2.0);
        } playing = !playing;
    } else {
        if (playing == true) {
            SetMousePosition(GetRenderWidth() / 2.0, GetRenderHeight() / 2.0);
        }
    }
}
