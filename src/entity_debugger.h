#ifndef ENTITY_DEBUGGER
#define ENTITY_DEBUGGER

#include "globals.h"
#include "raygui.h"
#include "raylib.h"
#include "world.h"

void GuiWindowFloating(World *world, Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing,
                       Vector2 content_size, Vector2 *scroll, const char *title);
#endif
