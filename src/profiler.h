#ifndef PROFILER_H
#define PROFILER_H

#include "stdbool.h"
#define MAX_PROFILER_SECTIONS 32
#define MAX_NAME_LENGTH 32

typedef struct {
    char name[MAX_NAME_LENGTH];
    double start_time;
    double total_time;
    int call_count;
} ProfilerSection;

typedef struct {
    ProfilerSection sections[MAX_PROFILER_SECTIONS];
    int section_count;
} Profiler;

extern Profiler profiler;
extern bool profiler_enable;

void profiler_begin(const char *name);
void profiler_end(const char *name);
void profiler_reset(void);
void profiler_draw(int x, int y);

#define PROFILE_BEGIN(name) profiler_begin(name)
#define PROFILE_END(name) profiler_end(name)

#endif
