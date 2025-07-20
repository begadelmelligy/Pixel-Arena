#include "../../systems/render.h"
#include "raylib.h"
#include <math.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void highlight_summon(World *world, EntityType type, int num_entities, enum Formation formation)
{
    double angle = 2 * PI / num_entities;

    cSprite summon_type = all_entitites_types[type];

    Rectangle srcRect = {
        .x = summon_type.sprite_col * world->sprite_manager->glad_sprite_width,
        .y = summon_type.sprite_row * world->sprite_manager->glad_sprite_height,
        .width = world->sprite_manager->glad_sprite_width * summon_type.direction,
        .height = summon_type.sprite_height,
    };

    int size_x = world->sprite_manager->glad_sprite_width * 3;
    int size_y = world->sprite_manager->glad_sprite_height * 3;

    switch (formation) {
        case CIRCLE:
            for (int i = 0; i < num_entities; i++) {
                double x = world->keys.mouse_position.x + 10 * cos(i * angle);
                double y = world->keys.mouse_position.y + 10 * sin(i * angle);
                /*DrawCircle(x, y, 10, (Color){255, 0, 0, 127});*/
                Rectangle srcDest = {
                    .x = x - (float)(size_x) / 2,
                    .y = y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };

                DrawTexturePro(world->sprite_manager->glad_texture, srcRect, srcDest, (Vector2){x, y}, 0.0f,
                               (Color){0, 0, 0, 127});
            }
            break;

        case RECTANGLE:
            for (int i = 0; i < num_entities; i++) {
                double x = world->keys.mouse_position.x + world->adj_para.scroll_summon_spacing * i;
                double y = world->keys.mouse_position.y;
                Rectangle srcDest = {
                    .x = x - (float)(size_x) / 2,
                    .y = y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };

                DrawCircle(x, y, 10, (Color){255, 0, 0, 127});
                DrawTexturePro(world->sprite_manager->glad_texture, srcRect, srcDest, (Vector2){x, y}, 0.0f, WHITE);
            }
            break;
    }
}

void draw_entities(World *world)
{
    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_SPRITE) | (1 << COMPONENT_TARGET);

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
    }
}

void sRender(World *world, float dt)
{
    (void)dt;
    char *text;

    BeginDrawing();
    ClearBackground(BLACK);

    // Debugging Section -------------------------------------------------------------------
    if (world->debug.inpector_is_visible) {
        GuiWindowFloating(world, &world->debug.window_position, &world->debug.window_size, &world->debug.minimized,
                          &world->debug.moving, &world->debug.resizing, world->debug.scroll_threshold,
                          &world->debug.scroll, "Entity Inspector");
    }
    //--------------------------------------------------------------------------------------

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
            /*debug_draw_grid(world);*/
            draw_entities(world);
            /*if (world->mouse_state == SUMMON_SELECT) {*/
            /*    highlight_summon(world, DARK_WIZARD, 10, RECTANGLE);*/
            /*}*/
            break;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:
            text = "COMBAT";
            DrawText(text, 800, 100, 30, RED);
            draw_entities(world);
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
