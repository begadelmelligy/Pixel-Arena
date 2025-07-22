#include "entity.h"
#include "globals.h"
#include "world.h"

int create_entity(World *world)
{
    int id;
    if (world->free_id_count > 0) {
        id = world->free_ids[--world->free_id_count];
        world->free_ids[world->free_id_count] = INVALID_ENTITY_ID;

    } else {
        if (world->entity_count >= MAX_ENTITIES)
            return INVALID_ENTITY_ID;

        id = world->entity_count++;
    }

    world->entities[id].id = id;
    world->entities[id].component_masks = 0;
    world->entities[id].tag_mask = 0;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        world->entities[id].component_indices[i] = INVALID_COMPONENT_INDEX;
    }

    return id;
}

void destroy_entity(World *world, int entity_id)
{
    if (entity_id < 0 || entity_id >= MAX_ENTITIES || world->entities[entity_id].id == INVALID_ENTITY_ID)
        return;

    for (int i = 0; i < NUM_COMPONENT_TYPES; i++) {
        if (world->entities[entity_id].component_indices[i] != INVALID_COMPONENT_INDEX) {
            remove_component(world, entity_id, i);
        }
    }

    world->entities[entity_id].id = INVALID_ENTITY_ID;
    world->entities[entity_id].tag_mask = 0;
    world->entities[entity_id].component_masks = 0;

    if (world->free_id_count < MAX_ENTITIES) {
        world->free_ids[world->free_id_count++] = entity_id;
    }
}
