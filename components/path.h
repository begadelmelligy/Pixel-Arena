#ifndef PATH_H
#define PATH_H

#include "../src/support/grid.h"

typedef struct PathRequest {
    int target_x;
    int target_y;
    bool pending;
} PathRequest;

typedef struct cPath {
    Node *nodes[GRID_WIDTH * GRID_HEIGHT];
    int length;
    int current_index;
    bool active;
    PathRequest request;
} cPath;

void freePath(void *component_data);

#endif
