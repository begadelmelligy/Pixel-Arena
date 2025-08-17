#include "entity_debugger.h"
#include "../ecs_core/entity.h"
#include "../helper.h"
#include "raygui.h"
#include <stdio.h>

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

static void DrawContent(World *world, Vector2 position, Vector2 scroll)
{
    int offsetY = 40;

    // Entities buttons
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (world->entities[i].id == INVALID_ENTITY_ID)
            continue;

        Rectangle entities_button = {position.x + 20 + scroll.x, position.y + offsetY + scroll.y, 150, 25};
        Rectangle remove_entities_button = {position.x + 200 + scroll.x, position.y + offsetY + scroll.y, 25, 25};

        char toggle_label[128];
        snprintf(toggle_label, sizeof(toggle_label), "%s %s", world->debug.ele[i].is_toggled ? "-" : "+", world->debug.ele[i].name);

        if (GuiButton(entities_button, toggle_label)) {
            world->debug.ele[i].is_expanded = !world->debug.ele[i].is_expanded;
            world->debug.ele[i].is_toggled = !world->debug.ele[i].is_toggled;
        }
        if (GuiButton(remove_entities_button, "x")) {
            destroy_entity(world, i);
        }

        offsetY += 30;

        // Expand entities to view components
        if (world->debug.ele[i].is_expanded) {
            for (int j = 0; j < NUM_COMPONENT_TYPES; j++) {
                if (world->entities[i].component_indices[j] == INVALID_COMPONENT_INDEX)
                    continue;

                Rectangle comp_label_rect = {position.x + 20 + scroll.x, position.y + offsetY + scroll.y, 150, 20};
                Rectangle remove_comp_button = {position.x + 150 + scroll.x, position.y + offsetY + scroll.y, 20, 20};

                enum ComponentType type = j;
                GuiLabel(comp_label_rect, get_component_type_name(type));
                if (GuiButton(remove_comp_button, "x")) {
                    printf("Component Removed: %s\n", get_component_type_name(type));
                    remove_component(world, i, j);
                }
                offsetY += 20;
            }
        }
        offsetY += 5;
    }
}

void GuiWindowFloating(World *world, Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing, Vector2 content_size,
                       Vector2 *scroll, const char *title)
{

    int close_title_size_delta_half = (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

    // window movement and resize input and collision check
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !*moving && !*resizing) {
        Vector2 mouse_position = GetMousePosition();

        Rectangle title_collision_rect = {position->x, position->y,
                                          size->x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
                                          RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT};
        Rectangle resize_collision_rect = {position->x + size->x - 20, position->y + size->y - 20, 20, 20};

        if (CheckCollisionPointRec(mouse_position, title_collision_rect)) {
            *moving = true;
        } else if (!*minimized && CheckCollisionPointRec(mouse_position, resize_collision_rect)) {
            *resizing = true;
        }
    }

    // window movement and resize update
    if (*moving) {
        Vector2 mouse_delta = GetMouseDelta();
        position->x += mouse_delta.x;
        position->y += mouse_delta.y;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            *moving = false;

            // clamp window position keep it inside the application area
            if (position->x < 0)
                position->x = 0;
            else if (position->x > GetScreenWidth() - size->x)
                position->x = GetScreenWidth() - size->x;
            if (position->y < 0)
                position->y = 0;
            else if (position->y > GetScreenHeight())
                position->y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
        }

    } else if (*resizing) {
        Vector2 mouse = GetMousePosition();
        if (mouse.x > position->x)
            size->x = mouse.x - position->x;
        if (mouse.y > position->y)
            size->y = mouse.y - position->y;

        // clamp window size to an arbitrary minimum value and the window size as the maximum
        if (size->x < 100)
            size->x = 100;
        else if (size->x > GetScreenWidth())
            size->x = GetScreenWidth();
        if (size->y < 100)
            size->y = 100;
        else if (size->y > GetScreenHeight())
            size->y = GetScreenHeight();

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            *resizing = false;
        }
    }

    // window and content drawing with scissor and scroll area
    if (*minimized) {
        GuiStatusBar((Rectangle){position->x, position->y, size->x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, title);

        if (GuiButton((Rectangle){position->x + size->x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                                  position->y + close_title_size_delta_half, RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                                  RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
                      "#120#")) {
            *minimized = false;
        }

    } else {
        *minimized = GuiWindowBox((Rectangle){position->x, position->y, size->x, size->y}, title);

        // scissor and draw content within a scroll panel
        Rectangle scissor = {0};
        GuiScrollPanel(
            (Rectangle){position->x, position->y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size->x, size->y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT},
            NULL, (Rectangle){position->x, position->y, content_size.x, content_size.y}, scroll, &scissor);

        bool require_scissor = size->x < content_size.x || size->y < content_size.y;

        if (require_scissor) {
            BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
        }

        DrawContent(world, *position, *scroll);

        if (require_scissor) {
            EndScissorMode();
        }

        // draw the resize button/icon
        GuiDrawIcon(71, position->x + size->x - 20, position->y + size->y - 20, 1, WHITE);
    }
}
