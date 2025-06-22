#include "../../systems/render.h"
#include "raylib.h"
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void sRender(World *world, float dt)
{
    (void)dt;
    char *text;
    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_SPRITE);

    BeginDrawing();
    ClearBackground(BLACK);

    switch (world->game_state.game_state) {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case TITLE_SCREEN:
            GuiSetStyle(DEFAULT, TEXT_SIZE, 36);
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
                /*DrawCircle((int)pos->x, (int)pos->y, 2, RED);*/
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
                /*DrawCircle((int)pos->x, (int)pos->y, 2, RED);*/
            }

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
