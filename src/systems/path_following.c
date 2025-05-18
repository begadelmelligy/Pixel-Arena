#include "../../systems/path_following.h"
#include "stdio.h"

#define PATH_REACH_THRESHOLD 5.0f

void sPathFollowing(World *world, float dt)
{
    (void)dt;

    ComponentMask required_comp =
        (1 << COMPONENT_POSITION) | (1 << COMPONENT_VELOCITY) | (1 << COMPONENT_GRIDPOSITION) | (1 << COMPONENT_PATH);

    if (!world->game_state.is_paused) {

        for (int i = 0; i < MAX_ENTITIES; i++) {
            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
            int vel_idx = world->entities[i].component_indices[COMPONENT_VELOCITY];
            int grid_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int path_idx = world->entities[i].component_indices[COMPONENT_PATH];

            cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
            cVelocity *vel = &((cVelocity *)world->component_pools[COMPONENT_VELOCITY].data)[vel_idx];
            cGridPosition *grid = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_idx];
            cPath *path = &((cPath *)world->component_pools[COMPONENT_PATH].data)[path_idx];

            if (!path->active || path->current_index >= path->length - 1) {
                vel->dx = 0;
                vel->dy = 0;
                if (path->active && path->current_index >= path->length - 1) {
                    path->active = false;
                }
                continue;
            }

            /*printf("Path Following:\n");*/
            /*for (int i = 0; i < path->length; i++) {*/
            /*    if (path->nodes[i] != NULL) {*/
            /*        printf("(%d, %d)\n", path->nodes[i]->x, path->nodes[i]->y);*/
            /*    } else {*/
            /*        printf("NULL node at index %d\n", i);*/
            /*    }*/
            /*}*/

            Node *target = path->nodes[path->current_index];
            if (target == NULL) {
                fprintf(stderr, "Path node at index %d is NULL\n", path->current_index);
                path->active = false;
                vel->dx = 0;
                vel->dy = 0;
                continue;
            }

            float target_x = target->x * CELL_SIZE + CELL_SIZE / 2.f;
            float target_y = target->y * CELL_SIZE + CELL_SIZE / 2.f;
            float dx = target_x - pos->x;
            float dy = target_y - pos->y;
            float dist = sqrtf(dx * dx + dy * dy);

            if (dist < PATH_REACH_THRESHOLD) {
                pos->x = target_x;
                pos->y = target_y;
                grid->x = target->x;
                grid->y = target->y;
                path->current_index++;

                if (path->current_index >= path->length - 1) {
                    path->active = false;
                    vel->dx = 0;
                    vel->dy = 0;
                }
            } else {

                vel->dx = (dx / dist) * vel->speed;
                vel->dy = (dy / dist) * vel->speed;
            }
        }
    }
}

void sPathRequest(World *world, float dt)
{
    (void)dt;
    ComponentMask required_comp = (1 << COMPONENT_GRIDPOSITION) | (1 << COMPONENT_PATH) | (1 << COMPONENT_TARGET);

    if (!world->game_state.is_paused) {
        for (int i = 0; i < MAX_ENTITIES; i++) {

            if (world->entities[i].id == INVALID_ENTITY_ID)
                continue;
            if ((world->entities[i].component_masks & required_comp) == 0)
                continue;

            int grid_idx = world->entities[i].component_indices[COMPONENT_GRIDPOSITION];
            int path_idx = world->entities[i].component_indices[COMPONENT_PATH];

            cGridPosition *grid = &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_idx];
            cPath *path = &((cPath *)world->component_pools[COMPONENT_PATH].data)[path_idx];

            if ((!path->active && path->request.pending)) {

                for (int i = 0; i < path->length; i++) {
                    path->nodes[i] = NULL;
                }
                path->length = 0;
                path->current_index = 0;
                path->active = false;

                Node *start = &world->grid.node[grid->y][grid->x];
                Node *goal = &world->grid.node[path->request.target_y][path->request.target_x];

                /*printf("Starting Pathfind\n");*/
                a_star(world, start, goal, path);
            }
        }
    }
}
