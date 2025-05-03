#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define CELL_SIZE 32


typedef struct Node {
    int x, y;
    int g, h, f;
    bool walkable;
    int closed;
    int open;
    struct Node* parent;
    int entity_id;
} Node;


typedef struct NodeList {
    Node* nodes[GRID_WIDTH * GRID_HEIGHT];
    int count;
} NodeList;


typedef struct Grid {
    Node grid[GRID_HEIGHT][GRID_WIDTH];
} Grid;


#endif 
