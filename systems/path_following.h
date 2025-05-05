#ifndef PATH_FOLLOWING_H
#define PATH_FOLLOWING_H

#include "../src/world.h"
#include "../src/astar.h"

void sPathFollowing(World *world, float dt);
void sPathRequest(World *world, float dt);

#endif
