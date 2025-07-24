#include "../../systems/summon.h"
#include "../entity.h"
#include <stdio.h>

void summon_entities(World *world, SummonEvent summon_event)
{
    printf("Summoning type: %d, Count: %d, Formation: %d, x1: %f, y1: %f, x2: %f, y2: %f, x3: %f, y3: %f\n",
           summon_event.type, summon_event.num_entities, summon_event.formation, summon_event.x[0], summon_event.y[0],
           summon_event.x[1], summon_event.y[1], summon_event.x[2], summon_event.y[2]);

    for (int i = 0; i < summon_event.num_entities; i++) {
        int id = create_entity(world);
        if (id != INVALID_ENTITY_ID) {
            world->entities[id].tag_mask |= TAG_PLAYER_CREEPS;

            cPosition p = {.x = summon_event.x[i], .y = summon_event.y[i]};
            cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
            cSprite entity_sprite = all_entitites_types[summon_event.type];
            cSprite sprite = {
                .spritesheet = world->sprite_manager->glad_texture,
                .sprite_height = world->sprite_manager->glad_sprite_height,
                .sprite_width = world->sprite_manager->glad_sprite_width,
                .sprite_row = entity_sprite.sprite_row,
                .sprite_col = entity_sprite.sprite_col,
                .direction = entity_sprite.direction,
            };
            cHealth h = {.max_health = 100, .current_health = 100};
            cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

            add_component(world, id, COMPONENT_POSITION, &p);
            add_component(world, id, COMPONENT_VELOCITY, &v);
            add_component(world, id, COMPONENT_HEALTH, &h);
            add_component(world, id, COMPONENT_GRIDPOSITION, &g);
            add_component(world, id, COMPONENT_SPRITE, &sprite);
        }
    }
}

void sSummon(World *world, float dt)
{
    (void)dt;

    EventHandler *event_handler = &world->event_handler;

    for (int i = 0; i < event_handler->summon_count; i++) {
        Event e = event_handler->events[i];
        summon_entities(world, e.summon);
    }
    event_handler->summon_count = 0;
}
