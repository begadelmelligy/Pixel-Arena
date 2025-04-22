#include "game.h"


void InitGame(Game *game) {
    game->running = true;
}


void UpdateGame(Game *game, float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        game->running = false; // Allow quitting with ESC
    }
}


void DrawGame(const Game *game) {
    BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Alpha", 10, 10, 20, WHITE);
    EndDrawing();
}
