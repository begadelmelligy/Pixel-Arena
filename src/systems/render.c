#include "../../systems/render.h"
#include "../../components/position.h"
#include "../dev_tools/entity_debugger.h"
#include "../dev_tools/profiler.h"
#include "../game/data/entity_data.h"
#include "raylib.h"
#include <math.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Draws entities with the correct direction
void draw_entities(World *world)
{
    ComponentMask required_comp = (1 << COMPONENT_POSITION) | (1 << COMPONENT_SPRITE) | (1 << COMPONENT_TARGET);

    for (int i = 0; i < MAX_ENTITIES; i++) {

        if (world->entities[i].id == INVALID_ENTITY_ID)
            continue;
        if ((world->entities[i].component_masks & required_comp) != required_comp)
            continue;

        int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
        int target_idx = world->entities[i].component_indices[COMPONENT_TARGET];
        int sprite_idx = world->entities[i].component_indices[COMPONENT_SPRITE];
        cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];
        cTarget *target = &((cTarget *)world->component_pools[COMPONENT_TARGET].data)[target_idx];
        cSprite *sprite = &((cSprite *)world->component_pools[COMPONENT_SPRITE].data)[sprite_idx];

        if (target->current_target != INVALID_ENTITY_ID &&
            world->entities[target->current_target].component_indices[COMPONENT_POSITION] != INVALID_COMPONENT_INDEX) {
            int target_pos_idx = world->entities[target->current_target].component_indices[COMPONENT_POSITION];
            cPosition *target_pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[target_pos_idx];
            float dx = target_pos->x - pos->x;
            float dir_x = (dx == 0) ? 1 : dx / fabs(dx);
            sprite->direction = -dir_x; // Negative because the sprites are aiming to the left nominally
        }

        Rectangle srcRect = {
            .x = sprite->sprite_col * sprite->sprite_sheet_data.sprite_width,
            .y = sprite->sprite_row * sprite->sprite_sheet_data.sprite_height,
            .width = sprite->sprite_sheet_data.sprite_width * sprite->direction,
            .height = sprite->sprite_sheet_data.sprite_height,
        };

        int size_x = sprite->sprite_sheet_data.sprite_width * sprite->sprite_multi;
        int size_y = sprite->sprite_sheet_data.sprite_height * sprite->sprite_multi;

        Rectangle srcDest = {
            .x = pos->x - (float)(size_x) / 2,
            .y = pos->y - (float)(size_y) / 2,
            .width = size_x,
            .height = size_y,
        };

        DrawTexturePro(sprite->sprite_sheet_data.sprite_sheet, srcRect, srcDest, (Vector2){0, 0}, 0.0f, WHITE);
        /*DrawCircle((int)pos->x, (int)pos->y, 5, RED);*/
        if ((world->entities[i].component_masks & (1 << COMPONENT_BOUNDING_RECT)) == (1 << COMPONENT_BOUNDING_RECT)) {
            int bounding_box_idx = world->entities[i].component_indices[COMPONENT_BOUNDING_RECT];
            cBoundingRect *bounding_box = &((cBoundingRect *)world->component_pools[COMPONENT_BOUNDING_RECT].data)[bounding_box_idx];

            if (bounding_box->is_visible) {
                DrawRectangleLines(bounding_box->rect.x, bounding_box->rect.y, bounding_box->rect.width, bounding_box->rect.height, WHITE);
            }
        }
    }
}

void sRender(World *world, float dt)
{
    PROFILE_BEGIN("System Render");
    (void)dt;
    char *text;

    BeginDrawing();
    ClearBackground(BLACK);

    // Debugging Section -------------------------------------------------------------------
    if (world->debug.inpector_is_visible) {
        GuiWindowFloating(world, &world->debug.window_position, &world->debug.window_size, &world->debug.minimized, &world->debug.moving,
                          &world->debug.resizing, world->debug.scroll_threshold, &world->debug.scroll, "Entity Inspector");
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
            draw_entities(world);
            if (world->mouse_state == SUMMON_SELECT) {
                highlight_summon(world, world->event.summon);
            }
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

    PROFILE_END("System Render");
}

void highlight_summon(World *world, SummonEvent summon_event)
{
    float angle = 2 * PI / summon_event.num_entities;

    EntityTemplate summon_type = entity_template[summon_event.type];
    SpriteSheetData sprite_sheet_data = get_sprite_sheet(&world->sprite_manager, summon_type.sprite_sheet_type);

    Rectangle srcRect = {
        .x = summon_type.sprite.sprite_col * sprite_sheet_data.sprite_width,
        .y = summon_type.sprite.sprite_row * sprite_sheet_data.sprite_height,
        .width = sprite_sheet_data.sprite_width * summon_type.sprite.direction,
        .height = sprite_sheet_data.sprite_height,
    };
    int size_x = sprite_sheet_data.sprite_width * 3;
    int size_y = sprite_sheet_data.sprite_height * 3;

    switch (summon_event.formation) {
        case CIRCLE:
            for (int i = 0; i < summon_event.num_entities; i++) {
                float x = world->keys.mouse_position.x + world->adj_para.scroll_summon_spacing * cos(i * angle);
                float y = world->keys.mouse_position.y + world->adj_para.scroll_summon_spacing * sin(i * angle);
                world->event.summon.x[i] = x;
                world->event.summon.y[i] = y;
                Rectangle srcDest = {
                    .x = x - (float)(size_x) / 2,
                    .y = y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };
                DrawTexturePro(sprite_sheet_data.sprite_sheet, srcRect, srcDest, (Vector2){0, 0}, 0.0f, (Color){255, 255, 255, 127});
            }
            break;

        case RECTANGLE:
            for (int i = 0; i < summon_event.num_entities; i++) {
                float x = world->keys.mouse_position.x + world->adj_para.scroll_summon_spacing * i;
                float y = world->keys.mouse_position.y;
                Rectangle srcDest = {
                    .x = x - (float)(size_x) / 2,
                    .y = y - (float)(size_y) / 2,
                    .width = size_x,
                    .height = size_y,
                };
                DrawTexturePro(sprite_sheet_data.sprite_sheet, srcRect, srcDest, (Vector2){0, 0}, 0.0f, (Color){255, 255, 255, 127});
            }
            break;
    }
}
