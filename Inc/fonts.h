#ifndef FONTS_H_
#define FONTS_H_

#include "main.h"

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;

extern FontDef Font_15x25;

#endif /* FONTS_H_ */
