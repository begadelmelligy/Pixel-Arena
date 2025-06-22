#include "entity_data.h"

int summon_enemy_caster(World *world, SpriteManager *sm)
{

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag_mask |= TAG_ENEMY_HERO;

        cPosition p = {.x = 100.f, .y = 0.f};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
        cSprite sprite = {
            .spritesheet = sm->glad_texture,
            .sprite_height = sm->glad_sprite_height,
            .sprite_width = sm->glad_sprite_width,
            .sprite_row = 1,
            .sprite_col = 2,
        };
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cPath path = {.length = 0, .current_index = 0, .active = false};
        cTarget target = {.current_target = 0, .target_distance = 100000, .is_new = true, .is_active = false};
        cAIState state = {.current_state = STATE_IDLE, .next_state = STATE_EMPTY};
        cAbilityCaster ability_caster;

        ability_caster.ability_count = 1;

        float cd = 0.0f;
        dictInit(&ability_caster.remaining_cd, 1, sizeof(float));
        dictAdd(&ability_caster.remaining_cd, ABILITY_CHAIN_LIGHTNING, &cd);

        Ability ability1 = all_abilities[ABILITY_CHAIN_LIGHTNING];
        dictInit(&ability_caster.abilities, 1, sizeof(Ability));
        dictAdd(&ability_caster.abilities, ABILITY_CHAIN_LIGHTNING, &ability1);

        cCastRequest cast_request = {.ability_id = ABILITY_CHAIN_LIGHTNING, .target = 1, .is_active = true};

        add_component(world, id, COMPONENT_POSITION, &p);
        add_component(world, id, COMPONENT_VELOCITY, &v);
        add_component(world, id, COMPONENT_HEALTH, &h);
        add_component(world, id, COMPONENT_GRIDPOSITION, &g);
        add_component(world, id, COMPONENT_PATH, &path);
        add_component(world, id, COMPONENT_TARGET, &target);
        add_component(world, id, COMPONENT_AISTATE, &state);
        add_component(world, id, COMPONENT_ABILITY_CASTER, &ability_caster);
        add_component(world, id, COMPONENT_CAST_REQUEST, &cast_request);
        add_component(world, id, COMPONENT_SPRITE, &sprite);
    }

    return id;
}

int summon_test_entity(World *world, SpriteManager *sm)
{

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag_mask |= TAG_PLAYER_CREEPS;

        cPosition p = {.x = 300.f, .y = 300.f};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
        cSprite sprite = {
            .spritesheet = sm->glad_texture,
            .sprite_height = sm->glad_sprite_height,
            .sprite_width = sm->glad_sprite_width,
            .sprite_row = 1,
            .sprite_col = 1,
        };
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};

        add_component(world, id, COMPONENT_POSITION, &p);
        add_component(world, id, COMPONENT_VELOCITY, &v);
        add_component(world, id, COMPONENT_HEALTH, &h);
        add_component(world, id, COMPONENT_GRIDPOSITION, &g);
        add_component(world, id, COMPONENT_SPRITE, &sprite);
    }
    return id;
}
