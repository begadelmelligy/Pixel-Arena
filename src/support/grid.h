#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define CELL_SIZE 32

typedef struct Node {
    bool walkable;
    int x, y;
} Node;

typedef struct Grid {
    Node node[GRID_HEIGHT][GRID_WIDTH];
} Grid;

#endif
