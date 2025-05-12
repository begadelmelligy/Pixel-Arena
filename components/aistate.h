#ifndef AISTATE_H
#define AISTATE_H

#include "stdbool.h"
#define NUM_STATES 3

enum AIState {
    STATE_EMPTY = -1,
    STATE_IDLE = 0,
    STATE_CHASING = 1,
    STATE_COMBAT = 2,
};

typedef struct cAIState {
    enum AIState current_state;
    enum AIState next_state;
} cAIState;

bool transition(cAIState *aistate, enum AIState next_state);

#endif
