#ifndef LUPI_RAYLIB_SHIM_H
#define LUPI_RAYLIB_SHIM_H

/*
 * Just enough of raylib for lupinho's ui.c and lua_api.c to compile inside a
 * libretro core. Input is backed by the frontend; the texture helpers are
 * stubs because the core reads the framebuffer directly.
 */

#include <stdbool.h>
#include <stdint.h>

typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Image {
    void *data;
    int width;
    int height;
    int mipmaps;
    int format;
} Image;

typedef struct Texture {
    unsigned int id;
    int width;
    int height;
    int mipmaps;
    int format;
} Texture;

typedef Texture Texture2D;

typedef struct Rectangle {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

#define BLANK (Color){ 0, 0, 0, 0 }
#define WHITE (Color){ 255, 255, 255, 255 }

Image GenImageColor(int width, int height, Color color);
Texture2D LoadTextureFromImage(Image image);
void UnloadImage(Image image);
void UnloadTexture(Texture2D texture);
void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);

/* Values match raylib's GamepadButton, which Lua games already use. */
#define GAMEPAD_BUTTON_UNKNOWN           0
#define GAMEPAD_BUTTON_LEFT_FACE_UP      1
#define GAMEPAD_BUTTON_LEFT_FACE_RIGHT   2
#define GAMEPAD_BUTTON_LEFT_FACE_DOWN    3
#define GAMEPAD_BUTTON_LEFT_FACE_LEFT    4
#define GAMEPAD_BUTTON_RIGHT_FACE_UP     5
#define GAMEPAD_BUTTON_RIGHT_FACE_RIGHT  6
#define GAMEPAD_BUTTON_RIGHT_FACE_DOWN   7
#define GAMEPAD_BUTTON_RIGHT_FACE_LEFT   8
#define GAMEPAD_BUTTON_LEFT_TRIGGER_1    9
#define GAMEPAD_BUTTON_LEFT_TRIGGER_2   10
#define GAMEPAD_BUTTON_RIGHT_TRIGGER_1  11
#define GAMEPAD_BUTTON_RIGHT_TRIGGER_2  12
#define GAMEPAD_BUTTON_MIDDLE_LEFT      13
#define GAMEPAD_BUTTON_MIDDLE           14
#define GAMEPAD_BUTTON_MIDDLE_RIGHT     15
#define GAMEPAD_BUTTON_LEFT_THUMB       16
#define GAMEPAD_BUTTON_RIGHT_THUMB      17

#define KEY_A 1
#define KEY_D 2
#define KEY_G 3
#define KEY_H 4
#define KEY_J 5
#define KEY_K 6
#define KEY_L 7
#define KEY_M 8
#define KEY_S 9
#define KEY_W 10

bool IsGamepadButtonDown(int gamepad, int button);
bool IsGamepadButtonPressed(int gamepad, int button);
bool IsKeyDown(int key);
bool IsKeyPressed(int key);

#endif
