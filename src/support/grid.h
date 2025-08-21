#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define GRID_WIDTH 100
#define GRID_HEIGHT 100
#define CELL_SIZE 32

typedef struct Node {
    int entity_id;
    bool walkable;
    int x, y;
    int g, h, f;
    int closed; // A* closed list
    int open;   // A* open list
    struct Node *parent;
} Node;

typedef struct NodeList {
    Node *nodes[GRID_WIDTH * GRID_HEIGHT];
    int count;
} NodeList;

typedef struct Grid {
    Node node[GRID_HEIGHT][GRID_WIDTH];
} Grid;

#endif
