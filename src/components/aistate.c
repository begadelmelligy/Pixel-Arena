#include "../../components/aistate.h"
#include <stdio.h>

enum AIState next_legal_state[NUM_STATES][NUM_STATES - 1] = {
    [IDLE] = {CHASING, COMBAT},
    [CHASING] = {IDLE, COMBAT},
    [COMBAT] = {IDLE, CHASING},
};

bool transition(cAIState *aistate, enum AIState candidate)
{
    for (int i = 0; i < NUM_STATES; i++) {
        if (next_legal_state[aistate->current_state][i] == candidate) {
            aistate->next_state = candidate;
            printf("State Transition Success!");
            return true;
        }
    }
    printf("State Transition Fail.");
    return false;
}
