#include "helper.h"

void initialize_component_pool(World *world, enum ComponentType type, void *data, size_t component_size) {
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

void initialize_keys(World *world) {
    world->keys.mouse_position = (Vector2){0, 0};
    world->keys.left_click = 0;
    world->keys.right_click = 0;
    world->keys.key_shift = 0;
    world->keys.key_space = 0;
    world->keys.selected_menu_item = 0;
    world->keys.selected_unit_id = 0;
}
