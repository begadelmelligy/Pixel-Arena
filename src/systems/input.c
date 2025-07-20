#include "../../systems/input.h"
#include <stdio.h>

void sInput(World *world, float dt)
{
    (void)dt;
    world->keys.mouse_position = GetMousePosition();
    world->keys.mouse_wheel = GetMouseWheelMove();
    world->keys.left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    world->keys.right_click = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    world->keys.key_space = IsKeyPressed(KEY_SPACE);
    world->keys.key_s = IsKeyPressed(KEY_S);
    world->keys.key_shift = IsKeyDown(KEY_LEFT_SHIFT);
    world->keys.key_a = IsKeyDown(KEY_A);

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
            if (world->keys.key_s) {
                world->mouse_state = SUMMON_SELECT;
            }

            if (world->mouse_state == SUMMON_SELECT) {
                if (world->keys.mouse_wheel < 0) {
                    world->adj_para.scroll_summon_spacing -= 10;
                } else if (world->keys.mouse_wheel > 0) {
                    world->adj_para.scroll_summon_spacing += 10;
                }
            }

            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:

            if (world->keys.right_click) {
                summon_enemy_caster(world, world->keys.mouse_position.x, world->keys.mouse_position.y);
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
