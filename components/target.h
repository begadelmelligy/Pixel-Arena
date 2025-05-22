#ifndef TARGET_H
#define TARGET_H

#include "stdbool.h"

typedef struct cTarget {
    int current_target;
    float target_distance;
    bool is_new;
    bool is_active;
} cTarget;

#endif
