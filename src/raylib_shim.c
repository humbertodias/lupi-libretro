#include "raylib.h"

#include <string.h>

Image GenImageColor(int width, int height, Color color) {
    Image image;
    (void)color;
    memset(&image, 0, sizeof(image));
    image.width = width;
    image.height = height;
    return image;
}

Texture2D LoadTextureFromImage(Image image) {
    Texture2D texture;
    memset(&texture, 0, sizeof(texture));
    texture.width = image.width;
    texture.height = image.height;
    return texture;
}

void UnloadImage(Image image) {
    (void)image;
}

void UnloadTexture(Texture2D texture) {
    (void)texture;
}

void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) {
    (void)texture;
    (void)source;
    (void)dest;
    (void)origin;
    (void)rotation;
    (void)tint;
}
