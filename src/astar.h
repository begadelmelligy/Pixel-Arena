#ifndef ASTAR_H
#define ASTAR_H

#include "world.h"


int heuristic(Node *a, Node *b);
void add_to_open(NodeList* list, Node *node);
void remove_from_open(NodeList *list, Node *node);
Node* get_lowest_f(NodeList *list);
void reconstruct_path(Node *goal);

void a_star(World *world, Node *start, Node *goal);



#endif
