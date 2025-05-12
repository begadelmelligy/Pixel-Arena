#ifndef PATH_FOLLOWING_H
#define PATH_FOLLOWING_H

#include "../src/astar.h"
#include "../src/world.h"

void sPathFollowing(World *world, float dt);
void sPathRequest(World *world, float dt);

#endif
