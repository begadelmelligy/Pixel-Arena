#ifndef BOUNDING_RECT_H
#define BOUNDING_RECT_H

#include "raylib.h"
#include "stdbool.h"

typedef struct cBoundingRect {
    Rectangle rect;
    bool is_visible;
} cBoundingRect;

#endif
