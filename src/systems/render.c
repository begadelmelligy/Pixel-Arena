#include "raylib.h"
#include "../../systems/render.h"
#include "../../components/position.h"
#include <stdio.h>

void sRender(World *world, float dt) {
    (void)dt;
    char *text;

    BeginDrawing();
    ClearBackground(BLACK);


    switch(world->game_state.game_state) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case TITLE_SCREEN:
            text = "TITLE SCREEN";
            DrawText(text, 800, 100, 30, RED);
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
            for (int i = 0; i < world->entity_count; i++) {
                if (world->entities[i].id == INVALID_ENTITY_ID) continue;
                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                if (pos_idx != INVALID_COMPONENT_INDEX) {
                    cPosition* pos = &((cPosition*)world->component_pools[COMPONENT_POSITION].data)[pos_idx];


                    DrawCircle((int)pos->x, (int)pos->y, 50, RED);
                }
            }
            break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case COMBAT:
            text = "COMBAT";
            DrawText(text, 800, 100, 30, RED);
            for (int i = 0; i < world->entity_count; i++) {
                if (world->entities[i].id == INVALID_ENTITY_ID) continue;
                int pos_idx = world->entities[i].component_indices[COMPONENT_POSITION];
                if (pos_idx != INVALID_COMPONENT_INDEX) {
                    cPosition* pos = &((cPosition*)world->component_pools[COMPONENT_POSITION].data)[pos_idx];


                    DrawCircle((int)pos->x, (int)pos->y, 50, RED);
                }
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
