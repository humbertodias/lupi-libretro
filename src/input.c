#include "input.h"
#include "raylib.h"

#define LUPI_MAX_PADS    2
#define LUPI_MAX_BUTTONS 18

static bool button_down[LUPI_MAX_PADS][LUPI_MAX_BUTTONS];
static bool button_prev[LUPI_MAX_PADS][LUPI_MAX_BUTTONS];

void lupi_input_begin_frame(void) {
    for (int pad = 0; pad < LUPI_MAX_PADS; pad++) {
        for (int button = 0; button < LUPI_MAX_BUTTONS; button++) {
            button_prev[pad][button] = button_down[pad][button];
            button_down[pad][button] = false;
        }
    }
}

void lupi_input_set(int pad, int button, bool down) {
    if (pad < 0 || pad >= LUPI_MAX_PADS) return;
    if (button < 0 || button >= LUPI_MAX_BUTTONS) return;
    if (down) button_down[pad][button] = true;
}

static bool button_held(int pad, int button) {
    if (pad < 0 || pad >= LUPI_MAX_PADS) return false;
    if (button < 0 || button >= LUPI_MAX_BUTTONS) return false;
    return button_down[pad][button];
}

bool IsGamepadButtonDown(int gamepad, int button) {
    return button_held(gamepad, button);
}

bool IsGamepadButtonPressed(int gamepad, int button) {
    if (!button_held(gamepad, button)) return false;
    return !button_prev[gamepad][button];
}

bool IsKeyDown(int key) {
    (void)key;
    return false;
}

bool IsKeyPressed(int key) {
    (void)key;
    return false;
}
