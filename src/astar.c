#include "astar.h"
#include <stdio.h>


int heuristic(Node *a, Node *b) {
    return abs(a->x - b->x) + abs(a->y - b->y);
}

void add_to_open(NodeList *list, Node *node) {
    list->nodes[list->count++] = node;
    node->open = 1;
}


void remove_from_open(NodeList *list, Node *node) {
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


Node* get_lowest_f(NodeList *list) {
    Node* lowest = list->nodes[0];
    for (int i = 1; i < list->count; i++) {
        if (list->nodes[i]->f < lowest->f)
            lowest = list->nodes[i];
    }
    return lowest;
}


void reconstruct_path(Node *goal) {
    Node *current = goal;
    printf("Path:\n");
    while (current != NULL) {
        printf("(%d, %d)\n", current->x, current->y);
        current = current->parent;
    }
}


void a_star(World *world, Node *start, Node *goal) {
    NodeList open_list = { .count = 0 };
    add_to_open(&open_list, start);

    start->g = 0;
    start->h = heuristic(start, goal);
    start->f = start->h;

    while (open_list.count > 0) {
        Node *current = get_lowest_f(&open_list);
        if (current == goal) {
            reconstruct_path(goal);
            return;
        }

        remove_from_open(&open_list, current);
        current->closed = 1;

        int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        for (int i = 0; i < 4; i++) {
            int nx = current->x + dirs[i][0];
            int ny = current->y + dirs[i][1];

            if (nx < 0 || ny < 0 || nx >= GRID_WIDTH || ny >= GRID_HEIGHT)
                continue;

            Node *neighbor = &world->grid.grid[ny][nx];
            if (!neighbor->walkable || neighbor->closed)
                continue;

            int tentative_g = current->g + 1;
            if (!neighbor->open || tentative_g < neighbor->g) {
                neighbor->parent = current;
                neighbor->g = tentative_g;
                neighbor->h = heuristic(neighbor, goal);
                neighbor->f = neighbor->g + neighbor->h;

                if (!neighbor->open)
                    add_to_open(&open_list, neighbor);
            }
        }
    }

    printf("No path found.\n");
}
