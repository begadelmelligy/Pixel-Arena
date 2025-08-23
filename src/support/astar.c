#include "astar.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int heuristic(PathNode *a, PathNode *b) { return abs(a->x - b->x) + abs(a->y - b->y); }

void add_to_open(PathNodeList *list, PathNode *node)
{
    list->nodes[list->count++] = node;
    node->open = 1;
}

void remove_from_open(PathNodeList *list, PathNode *node)
{
    for (int i = 0; i < list->count; i++) {
        if (list->nodes[i] == node) {
            for (int j = i; j < list->count - 1; j++) {
                list->nodes[j] = list->nodes[j + 1];
            }
            list->count--;
            node->open = 0;
            return;
        }
    }
}

PathNode *get_lowest_f(PathNodeList *list)
{
    PathNode *lowest = list->nodes[0];
    for (int i = 1; i < list->count; i++) {
        if (list->nodes[i]->f < lowest->f)
            lowest = list->nodes[i];
    }
    return lowest;
}

void reconstruct_path(PathNode *goal, cPath *path, World *world)
{
    PathNode *current = goal;
    PathNode *temp_nodes[GRID_WIDTH * GRID_HEIGHT];
    int count = 0;

    // Build path backwards
    while (current != NULL) {
        temp_nodes[count++] = current;
        current = current->parent;
    }

    // Convert PathNodes back to world grid nodes and reverse order
    for (int i = 0; i < count; i++) {
        PathNode *path_node = temp_nodes[count - 1 - i];
        path->nodes[i] = &world->grid.node[path_node->y][path_node->x];
    }

    path->length = count;
    path->current_index = 0;
    path->active = true;
}

void a_star(World *world, Node *start, Node *goal, cPath *path)
{
    // Path Reset
    for (int i = 0; i < path->length; i++) {
        path->nodes[i] = NULL;
    }
    path->length = 0;
    path->current_index = 0;

    PathNode path_grid[GRID_HEIGHT][GRID_WIDTH];

    // Initialize pathfinding grid from world grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            PathNode *path_node = &path_grid[y][x];
            Node *world_node = &world->grid.node[y][x];

            path_node->x = x;
            path_node->y = y;
            path_node->walkable = world_node->walkable;
            path_node->f = path_node->g = path_node->h = 0;
            path_node->parent = NULL;
            path_node->closed = 0;
            path_node->open = 0;
        }
    }

    PathNodeList open_list = {.count = 0};

    PathNode *path_start = &path_grid[start->y][start->x];
    PathNode *path_goal = &path_grid[goal->y][goal->x];

    add_to_open(&open_list, path_start);
    path_start->g = 0;
    path_start->h = heuristic(path_start, path_goal);
    path_start->f = path_start->h;

    while (open_list.count > 0) {
        PathNode *current = get_lowest_f(&open_list);

        if (current == path_goal) {
            reconstruct_path(path_goal, path, world);
            return;
        }

        remove_from_open(&open_list, current);
        current->closed = 1;

        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int i = 0; i < 4; i++) {
            int nx = current->x + dirs[i][0];
            int ny = current->y + dirs[i][1];

            if (nx < 0 || ny < 0 || nx >= GRID_WIDTH || ny >= GRID_HEIGHT)
                continue;

            PathNode *neighbor = &path_grid[ny][nx];

            if (!neighbor->walkable || neighbor->closed)
                continue;

            int tentative_g = current->g + 1;

            if (!neighbor->open || tentative_g < neighbor->g) {
                neighbor->parent = current;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(neighbor, path_goal);
                neighbor->f = neighbor->g + neighbor->h;

                if (!neighbor->open)
                    add_to_open(&open_list, neighbor);
            }
        }
    }

    printf("No path found.\n");
    path->active = false;
    path->length = 0;
}
