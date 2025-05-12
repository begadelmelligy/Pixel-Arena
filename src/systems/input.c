#include "../../systems/input.h"
#include <stdio.h>

void sInput(World *world, float dt)
{
    (void)dt;
    world->keys.mouse_position = GetMousePosition();
    world->keys.left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    world->keys.right_click = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    world->keys.key_space = IsKeyPressed(KEY_SPACE);
    world->keys.key_shift = IsKeyPressed(KEY_LEFT_SHIFT);

    switch (world->game_state.game_state) {
        case TITLE_SCREEN:
            if (world->keys.key_space) {
                world->game_state.game_state = HUB;
                world->game_state.is_paused = true;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case HUB:
            if (world->keys.key_space) {
                world->game_state.game_state = WAVESETUP;
                world->game_state.is_paused = true;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case WAVESETUP:
            if (world->keys.key_space) {
                world->game_state.game_state = GAME_COMBAT;
                world->game_state.is_paused = false;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:
            if (world->keys.left_click) {
                int e = create_entity(world);
                if (e != INVALID_ENTITY_ID) {
                    world->entities[e].tag_mask |= TAG_PLAYER_CREEPS;
                    cPosition p = {world->keys.mouse_position.x, world->keys.mouse_position.y};
                    cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
                    add_component(world, e, COMPONENT_POSITION, &p);
                    add_component(world, e, COMPONENT_GRIDPOSITION, &g);
                }
            }

            if (world->keys.right_click) {
                cPosition p = {world->keys.mouse_position.x, world->keys.mouse_position.y};
                cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

                for (int i = 0; i < MAX_ENTITIES; i++) {
                    if (world->entities[i].id == INVALID_ENTITY_ID)
                        continue;

                    int grid_pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                    cGridPosition *pos =
                        &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];

                    if (g.x == pos->x && g.y == pos->y) {
                        destroy_entity(world, i);
                    }
                }
            }

            if (world->keys.key_space) {
                world->game_state.game_state = ENDGAME;
                world->game_state.is_paused = true;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case ENDGAME:
            if (world->keys.key_space) {
                world->game_state.game_state = HUB;
                world->game_state.is_paused = true;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
