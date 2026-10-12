#ifndef LUPI_INPUT_H
#define LUPI_INPUT_H

#include <stdbool.h>

void lupi_input_begin_frame(void);
void lupi_input_set(int pad, int button, bool down);

#endif
