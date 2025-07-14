#include "../../systems/render.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void sRender(World *world, float dt)
{
    (void)dt;
    char *text;
    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_SPRITE) | (1 << COMPONENT_TARGET);

    BeginDrawing();
    ClearBackground(BLACK);

    switch (world->game_state.game_state) {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case TITLE_SCREEN:
            GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
            if (GuiButton((Rectangle){WIDTH / 2 - WIDTH * 0.25 / 2, HEIGHT * 0.5, WIDTH * 0.25, 100}, "Start Game")) {
                world->game_state.game_state = HUB;
            }
            if (GuiButton((Rectangle){WIDTH / 2 - WIDTH * 0.25 / 2, HEIGHT * 0.7, WIDTH * 0.25, 100}, "QUIT Game")) {
                destroy_world(world);
            }
            break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case HUB:
            text = "HUB";
            DrawText(text, 800, 100, 30, RED);
            break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case WAVESETUP:
            text = "SETUP WAVE";
            DrawText(text, 800, 100, 30, RED);
            debug_draw_grid(world);

            for (int i = 0; i < MAX_ENTITIES; i++) {

                if (world->entities[i].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[i].component_masks & required_comp) == 0)
                    continue;

                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                int sprite_idx = world->entities[i].component_indices[COMPONENT_SPRITE];
                cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
                cSprite *sprite = &((cSprite *)world->component_pools[COMPONENT_SPRITE].data)[sprite_idx];

                Rectangle srcRect = {
                    .x = sprite->sprite_col * sprite->sprite_width,
                    .y = sprite->sprite_row * sprite->sprite_height,
                    .width = sprite->sprite_width,
                    .height = sprite->sprite_height,
                };

                int size_x = sprite->sprite_width * 3;
                int size_y = sprite->sprite_height * 3;

                Rectangle srcDest = {
                    .x = pos->x - (float)(size_x) / 2,
                    .y = pos->y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };

                DrawTexturePro(sprite->spritesheet, srcRect, srcDest, (Vector2){0, 0}, 0.0f, WHITE);
                DrawCircle((int)pos->x, (int)pos->y, 5, RED);
            }
            break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:
            text = "COMBAT";
            DrawText(text, 800, 100, 30, RED);

            for (int i = 0; i < MAX_ENTITIES; i++) {

                if (world->entities[i].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[i].component_masks & required_comp) == 0)
                    continue;

                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];
                int sprite_idx = world->entities[i].component_indices[COMPONENT_SPRITE];
                cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
                cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];
                cSprite *sprite = &((cSprite *)world->component_pools[COMPONENT_SPRITE].data)[sprite_idx];

                int target_pos_idx = world->entities[target->current_target].component_indices[COMPONENT_POSITION];
                cPosition *target_pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[target_pos_idx];

                if (target->current_target != INVALID_ENTITY_ID) {
                    float dir_x = (target_pos->x - pos->x) / fabs(target_pos->x - pos->x);
                    sprite->direction = -dir_x; // Negative because the sprites are aiming to the left nominally
                }

                Rectangle srcRect = {
                    .x = sprite->sprite_col * sprite->sprite_width,
                    .y = sprite->sprite_row * sprite->sprite_height,
                    .width = sprite->sprite_width * sprite->direction,
                    .height = sprite->sprite_height,
                };

                int size_x = sprite->sprite_width * 3;
                int size_y = sprite->sprite_height * 3;

                Rectangle srcDest = {
                    .x = pos->x - (float)(size_x) / 2,
                    .y = pos->y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };

                DrawTexturePro(sprite->spritesheet, srcRect, srcDest, (Vector2){0, 0}, 0.0f, WHITE);
                DrawCircle((int)pos->x, (int)pos->y, 5, RED);
                // Debugging Section ---------------------------------------------------------------
            }
            if (world->debug.inpector_is_visible) {
                GuiWindowFloating(world, &world->debug.window_position, &world->debug.window_size,
                                  &world->debug.minimized, &world->debug.moving, &world->debug.resizing,
                                  world->debug.scroll_threshold, &world->debug.scroll, "Entity Inspector");
            }
            //---------------------------------------------------------------------------------

            break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case ENDGAME:
            text = "END GAME";
            DrawText(text, 800, 100, 30, RED);
            break;
    }

    DrawFPS(10, 10);
    EndDrawing();
}
