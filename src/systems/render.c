#include "../../systems/render.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void sRender(World *world, float dt)
{
    (void)dt;
    char *text;

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
            for (int i = 0; i < world->entity_count; i++) {
                if (world->entities[i].id == INVALID_ENTITY_ID)
                    continue;
                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                if (pos_idx != INVALID_COMPONENT_INDEX) {
                    cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];

                    DrawCircle((int)pos->x, (int)pos->y, 50, RED);
                }
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case GAME_COMBAT:
            text = "COMBAT";
            DrawText(text, 800, 100, 30, RED);

            ComponentMask required_comp = (1 << COMPONENT_POSITION);

            for (int i = 0; i < world->entity_count; i++) {

                if (world->entities[i].id == INVALID_ENTITY_ID)
                    continue;
                if ((world->entities[i].component_masks & required_comp) == 0)
                    continue;

                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                cPosition *pos = &((cPosition *)world->component_pools[COMPONENT_POSITION].data)[pos_idx];

                DrawCircle((int)pos->x, (int)pos->y, 50, RED);
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
