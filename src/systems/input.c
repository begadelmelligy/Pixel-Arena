#include "../../systems/input.h"
#include <stdio.h>

void sInput(World *world, float dt)
{
    (void)dt;
    world->keys.mouse_position = GetMousePosition();
    world->keys.left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    world->keys.right_click = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    world->keys.key_space = IsKeyPressed(KEY_SPACE);
    world->keys.key_shift = IsKeyDown(KEY_LEFT_SHIFT);
    world->keys.key_a = IsKeyDown(KEY_A);

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
            // Debugging Section ---------------------------------------------------------------
            world->debug.inpector_toggle_keys = world->keys.key_shift && world->keys.key_a;

            if (world->debug.inpector_toggle_keys && world->debug.can_toggle_inspector) {
                world->debug.inpector_is_visible = !world->debug.inpector_is_visible;
                world->debug.can_toggle_inspector = false;
            }

            if (!world->keys.key_shift || !world->keys.key_a) {
                world->debug.can_toggle_inspector = true;
            }
            //---------------------------------------------------------------------------------

            if (world->keys.right_click) {
                summon_test_entity(world, world->sprite_manager, world->keys.mouse_position.x,
                                   world->keys.mouse_position.y);
            }

            /*if (world->keys.right_click) {*/
            /*    cPosition p = {world->keys.mouse_position.x, world->keys.mouse_position.y};*/
            /*    cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};*/
            /**/
            /*    for (int i = 0; i < MAX_ENTITIES; i++) {*/
            /*        if (world->entities[i].id == INVALID_ENTITY_ID)*/
            /*            continue;*/
            /**/
            /*        int grid_pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];*/
            /*        cGridPosition *pos =*/
            /*            &((cGridPosition *)world->component_pools[COMPONENT_GRIDPOSITION].data)[grid_pos_idx];*/
            /**/
            /*        if (g.x == pos->x && g.y == pos->y) {*/
            /*            destroy_entity(world, i);*/
            /*        }*/
            /*    }*/
            /*    printf("Entities: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", world->entities[1].id,*/
            /*           world->entities[2].id, world->entities[3].id, world->entities[4].id, world->entities[5].id,*/
            /*           world->entities[6].id, world->entities[7].id, world->entities[8].id, world->entities[9].id,*/
            /*           world->entities[10].id);*/
            /*}*/

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
