#include "helper.h"
#include "globals.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

const char *ComponentTypeName[] = {"Position", "Velocity", "Health",         "Properties",   "Grid Position", "Path",
                                   "Target",   "AiState",  "Ability Caster", "Cast Request", "Sprite",        "AARR"};

void initialize_component_pool(World *world, enum ComponentType type, void *data, size_t component_size)
{
    if (type >= NUM_COMPONENT_TYPES) {
        return;
    }

    world->component_pools[type].data = data;
    world->component_pools[type].component_size = component_size;
    world->component_pools[type].free_count = 0;
    world->component_pools[type].active_count = 0;

    for (int i = 0; i < MAX_ENTITIES; i++) {
        world->component_pools[type].free_ids[i] = INVALID_COMPONENT_INDEX;
    }
}

void initialize_keys(World *world)
{
    world->keys.mouse_position = (Vector2){0, 0};
    world->keys.left_click = 0;
    world->keys.right_click = 0;
    world->keys.key_shift = 0;
    world->keys.key_space = 0;
    world->keys.selected_menu_item = 0;
    world->keys.selected_unit_id = 0;
}

void initialize_grid(World *world)
{
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            world->grid.node[y][x].walkable = true;
            world->grid.node[y][x].x = x;
            world->grid.node[y][x].y = y;
        }
    }
}

void initialize_debug_mode_parameters(World *world)
{
    for (int i = 0; i < MAX_ENTITIES; i++) {
        char temp[8];
        world->debug.ele[i].id = i;
        sprintf(temp, "%d", i);
        strcat(world->debug.ele[i].name, "Entity #");
        strcat(world->debug.ele[i].name, temp);

        world->debug.ele[i].is_toggled = false;
        world->debug.ele[i].is_expanded = false;
    }

    world->debug.can_toggle_inspector = false;
    world->debug.inpector_is_visible = false;
    world->debug.inpector_toggle_keys = false;

    world->debug.window_position = (Vector2){WIDTH - 275, 25};
    world->debug.window_size = (Vector2){250, 500};
    world->debug.minimized = false;
    world->debug.moving = false;
    world->debug.resizing = false;
    world->debug.scroll_threshold = (Vector2){300, HEIGHT};
    world->debug.scroll = (Vector2){0, 0};
    world->debug.profiler_vis = true;
    world->debug.AABR_vis = true;
}

const char *get_component_type_name(enum ComponentType type)
{
    if (type >= 0 && type < NUM_COMPONENT_TYPES) {
        return ComponentTypeName[type];
    }
    return "INVALID";
}

void debug_draw_grid(World *world)
{
    (void)world;
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
        }
    }
}
