#include "../../components/aistate.h"
#include <stdio.h>

enum AIState next_legal_state[NUM_STATES][NUM_STATES] = {
    [STATE_IDLE] = {STATE_CHASING, STATE_CASTING},
    [STATE_CHASING] = {STATE_IDLE, STATE_CASTING, STATE_CHASING},
    [STATE_CASTING] = {STATE_IDLE},
};

int next_legal_count[NUM_STATES] = {2, 3, 1};

bool transition(cAIState *aistate, enum AIState candidate)
{
    for (int i = 0; i < next_legal_count[aistate->current_state]; i++) {
        if (next_legal_state[aistate->current_state][i] == candidate) {
            aistate->next_state = candidate;
            /*printf("State Transition Success! %d -> %d\n", aistate->current_state, candidate);*/
            return true;
        }
    }
    /*printf("State Transition Fail.\n");*/
    return false;
}
