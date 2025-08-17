#ifndef ENTITY_DEBUGGER
#define ENTITY_DEBUGGER

#include "../world.h"
#include "raylib.h"

void GuiWindowFloating(World *world, Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing, Vector2 content_size,
                       Vector2 *scroll, const char *title);
#endif
