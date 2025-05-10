#ifndef PATH_H
#define PATH_H

#include "../src/grid.h"

typedef struct cPath {
    Node *nodes[GRID_WIDTH * GRID_HEIGHT];
    int length;
    int current_index;
    bool active;
} cPath;

typedef struct PathRequest {
    int target_x;
    int target_y;
    bool request_pending;
} PathRequest;

void freePath(void *component_data);

#endif
