#ifndef ASTAR_H
#define ASTAR_H

#include "../world.h"

typedef struct PathNode {
    int x, y;
    int g, h, f;
    int closed;
    int open;
    struct PathNode *parent;
    bool walkable;
} PathNode;

typedef struct PathNodeList {
    PathNode *nodes[GRID_WIDTH * GRID_HEIGHT];
    int count;
} PathNodeList;

/*Functions to help with A* Pathfinding*/
int heuristic(PathNode *a, PathNode *b);
void add_to_open(PathNodeList *list, PathNode *node);
void remove_from_open(PathNodeList *list, PathNode *node);
PathNode *get_lowest_f(PathNodeList *list);
void reconstruct_path(PathNode *goal, cPath *path, World *world);
void a_star(World *world, Node *start, Node *goal, cPath *path);
#endif
