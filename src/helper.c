#include "helper.h"
#include "grid.h"
#include "raylib.h"

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
            world->grid.node[y][x].entity_id = -1;
            world->grid.node[y][x].walkable = true;

            world->grid.node[y][x].x = x;
            world->grid.node[y][x].y = y;

            world->grid.node[y][x].g = 0;
            world->grid.node[y][x].h = 0;
            world->grid.node[y][x].f = 0;

            world->grid.node[y][x].closed = 0;
            world->grid.node[y][x].open = 0;

            world->grid.node[y][x].parent = NULL;
        }
    }
}

void debug_draw_grid(World *world)
{
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            DrawRectangleLines(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
        }
    }
}
