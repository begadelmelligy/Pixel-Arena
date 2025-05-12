#include "../../components/aistate.h"
#include <stdio.h>

enum AIState next_legal_state[NUM_STATES][NUM_STATES - 1] = {
    [STATE_IDLE] = {STATE_CHASING, STATE_COMBAT},
    [STATE_CHASING] = {STATE_IDLE, STATE_COMBAT},
    [STATE_COMBAT] = {STATE_IDLE, STATE_CHASING},
};

bool transition(cAIState *aistate, enum AIState candidate)
{
    for (int i = 0; i < NUM_STATES; i++) {
        if (next_legal_state[aistate->current_state][i] == candidate) {
            aistate->next_state = candidate;
            /*printf("State Transition Success!\n");*/
            return true;
        }
    }
    printf("State Transition Fail.\n");
    return false;
}
