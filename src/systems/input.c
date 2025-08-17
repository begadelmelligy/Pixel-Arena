#include "../../systems/input.h"
#include "../dev_tools/profiler.h"
#include "../game/data/entity_data.h"
#include <stdlib.h>

void sInput(World *world, float dt)
{
    PROFILE_BEGIN("System Input");
    (void)dt;
    world->keys.mouse_position = GetMousePosition();
    world->keys.mouse_wheel = GetMouseWheelMove();
    world->keys.left_click = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    world->keys.right_click = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    world->keys.key_space = IsKeyPressed(KEY_SPACE);
    world->keys.key_s = IsKeyPressed(KEY_S);
    world->keys.key_a = IsKeyPressed(KEY_A);
    world->keys.key_w = IsKeyPressed(KEY_W);
    world->keys.key_f2 = IsKeyPressed(KEY_F2);
    world->keys.key_f3 = IsKeyPressed(KEY_F3);
    world->keys.key_shift = IsKeyDown(KEY_LEFT_SHIFT);
    world->keys.key_a_down = IsKeyDown(KEY_A);

    // Debugging Section ---------------------------------------------------------------
    // Inspector START
    world->debug.inpector_toggle_keys = world->keys.key_shift && world->keys.key_a_down;

    if (world->debug.inpector_toggle_keys && world->debug.can_toggle_inspector) {
        world->debug.inpector_is_visible = !world->debug.inpector_is_visible;
        world->debug.can_toggle_inspector = false;
    }

    if (!world->keys.key_shift || !world->keys.key_a_down) {
        world->debug.can_toggle_inspector = true;
    }
    // Inpsector END

    // Profiler START
    if (world->keys.key_f2) {
        world->debug.profiler_vis = !world->debug.profiler_vis;
    }

    // AARR START
    if (world->keys.key_f3) {
        world->debug.AABR_vis = !world->debug.AABR_vis;
    }
    // AARR END

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

            // Change to Summon Select
            if (world->keys.key_s) {
                world->mouse_state = SUMMON_SELECT;
            }
            // SUMMON-STATE--------------------------------------------------------------------------------//
            if (world->mouse_state == SUMMON_SELECT) {
                if (world->keys.key_a) {
                    free(world->event.summon.x);
                    free(world->event.summon.y);
                    world->event.summon.num_entities = 1;
                    world->event.summon.formation = CIRCLE;
                    world->event.summon.type = DARK_WIZARD;
                    world->event.summon.x = malloc(sizeof(float) * world->event.summon.num_entities);
                    world->event.summon.y = malloc(sizeof(float) * world->event.summon.num_entities);
                }
                if (world->keys.key_s) {
                    free(world->event.summon.x);
                    free(world->event.summon.y);
                    world->event.summon.num_entities = 4;
                    world->event.summon.formation = CIRCLE;
                    world->event.summon.type = LIGHT_WIZARD;
                    world->event.summon.x = malloc(sizeof(float) * world->event.summon.num_entities);
                    world->event.summon.y = malloc(sizeof(float) * world->event.summon.num_entities);
                }
                if (world->keys.key_w) {
                    free(world->event.summon.x);
                    free(world->event.summon.y);
                    world->event.summon.num_entities = 4;
                    world->event.summon.formation = CIRCLE;
                    world->event.summon.type = BLUE_ANGEL;
                    world->event.summon.x = malloc(sizeof(float) * world->event.summon.num_entities);
                    world->event.summon.y = malloc(sizeof(float) * world->event.summon.num_entities);
                }

                if (world->keys.mouse_wheel < 0) {
                    world->adj_para.scroll_summon_spacing -= 10;
                } else if (world->keys.mouse_wheel > 0) {
                    world->adj_para.scroll_summon_spacing += 10;
                }

                if (world->keys.left_click) {
                    event_handler_push(&world->event_handler, EVENT_SUMMON, world->event);
                    world->mouse_state = FREE_MOUSE;
                }
            }
            //---------------------------------------------------------------------------------------------//

            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:

            if (world->keys.right_click) {
                summon_entity_template(world, LIGHT_WIZARD, world->keys.mouse_position.x, world->keys.mouse_position.y);
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
    PROFILE_END("System Input");
}
