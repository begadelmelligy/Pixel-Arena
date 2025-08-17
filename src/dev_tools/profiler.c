#include "profiler.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

#include "profiler.h"
#include <stdio.h>
#include <string.h>

Profiler profiler = {0};

void profiler_begin(const char *name)
{
    for (int i = 0; i < profiler.section_count; i++) {
        if (strcmp(profiler.sections[i].name, name) == 0) {
            profiler.sections[i].start_time = GetTime();
            return;
        }
    }

    if (profiler.section_count < MAX_PROFILER_SECTIONS) {
        ProfilerSection *section = &profiler.sections[profiler.section_count++];
        strncpy(section->name, name, MAX_NAME_LENGTH);
        section->start_time = GetTime();
        section->total_time = 0.0;
        section->call_count = 0;
    }
}

void profiler_end(const char *name)
{
    for (int i = 0; i < profiler.section_count; i++) {
        if (strcmp(profiler.sections[i].name, name) == 0) {
            double duration = GetTime() - profiler.sections[i].start_time;
            profiler.sections[i].total_time += duration;
            profiler.sections[i].call_count++;
            return;
        }
    }
}

void profiler_reset(void)
{
    for (int i = 0; i < profiler.section_count; i++) {
        profiler.sections[i].total_time = 0.0;
        profiler.sections[i].call_count = 0;
    }
}

void profiler_draw(int x, int y, Font font)
{
    for (int i = 0; i < profiler.section_count; i++) {
        ProfilerSection *s = &profiler.sections[i];
        double avg_time_ms = (s->call_count > 0) ? (s->total_time / s->call_count) * 1000.0 : 0.0;
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "%s: %.3f ms (%d)", s->name, avg_time_ms, s->call_count);
        DrawTextEx(font, buffer, (Vector2){x, y + i * 20}, 16, 2, RAYWHITE);
    }
}
