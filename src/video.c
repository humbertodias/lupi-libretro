#include "video.h"
#include "ui.h"

void present_frame_rgb565(uint16_t *out) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            Color c = get_palette_color(frame_buffer[y][x]);
            if (c.a == 0) {
                out[y * SCREEN_WIDTH + x] = 0;
                continue;
            }
            out[y * SCREEN_WIDTH + x] =
                (uint16_t)(((c.r >> 3) << 11) | ((c.g >> 2) << 5) | (c.b >> 3));
        }
    }
}
