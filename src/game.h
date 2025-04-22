#ifndef GAME_H
#define GAME_H


#include <raylib.h>


#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1200


typedef enum
{
    MAIN_MENU_SCENE,
    ARENA_SCENE,
    GAME_OVER_SCENE,
    VICTORY_SCENE

} GameScenes;


typedef struct
{
    GameScenes current_scene;

} GameState;


typedef struct {
    bool running;
} Game;


void InitGame(Game *game);
void UpdateGame(Game *game, float deltaTime);
void DrawGame(const Game *game);


#endif
