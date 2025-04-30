#include "../../systems/input.h"
#include "raylib.h"
#include <stdio.h>


void sInput(World *world, float dt) {
    (void)dt;
    world->keys.mouse_position = GetMousePosition();
    world->keys.left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    world->keys.right_click = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    world->keys.key_space = IsKeyPressed(KEY_SPACE);
    world->keys.key_shift = IsKeyPressed(KEY_LEFT_SHIFT);


    switch(world->game_state.game_state) {
        case TITLE_SCREEN:
            if (world->keys.key_space) {
                world->game_state.game_state = HUB;
            }
            break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case HUB:
            if (world->keys.key_space){
                world->game_state.game_state = WAVESETUP;
            }
            break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case WAVESETUP:
            if (world->keys.left_click) {
                int e = create_entity(world);
                if (e != INVALID_ENTITY_ID) {
                    cPosition p = {world->keys.mouse_position.x, world->keys.mouse_position.y};
                    cHealth h = {100, 100};
                    add_component(world, e, COMPONENT_POSITION, &p);
                    add_component(world, e, COMPONENT_HEALTH, &h);
                }

            }

            if (world->keys.key_space) {
                world->game_state.game_state = COMBAT;
            }
            break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case COMBAT:
            if (world->keys.key_space) {
                world->game_state.game_state = ENDGAME;
            }
            break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case ENDGAME:
            if (world->keys.key_space){
                world->game_state.game_state = TITLE_SCREEN;
            }
            break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

}
