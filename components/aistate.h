#ifndef AISTATE_H
#define AISTATE_H

#include "stdbool.h"
#define NUM_STATES 3

enum AIState {
    EMPTY = -1,
    IDLE = 0,
    CHASING = 1,
    COMBAT = 2,
};

typedef struct cAIState {
    enum AIState current_state;
    enum AIState next_state;
} cAIState;

bool transition(cAIState *aistate, enum AIState next_state);

#endif
