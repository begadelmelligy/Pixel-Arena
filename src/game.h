#ifndef GAME_H
#define GAME_H

#include <stdbool.h>


typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_BUILD_WAVE,
    GAME_STATE_COMBAT,
    GAME_STATE_GAME_OVER
} GameMode;


typedef struct {
    GameMode mode;
    int currentWave;
    int playerGold;
    int playerEvoToken;
    bool isPaused;
} GameState;


#endif
