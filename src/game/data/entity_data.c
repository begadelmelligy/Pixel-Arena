#include "entity_data.h"
#include "../../entity.h"
#include "ability_data.h"

cSprite all_entitites_types[ENTITY_TYPE_COUNT] = {
    [DARK_WIZARD] =
        {
            .sprite_row = 2,
            .sprite_col = 5,
            .direction = 1,
        },

    [LIGHT_WIZARD] =
        {
            .sprite_row = 2,
            .sprite_col = 6,
            .direction = 1,
        },
};

EntityTemplate entity_template[ENTITY_TYPE_COUNT] = {
    [DARK_WIZARD] =
        {
            .tag_mask = TAG_PLAYER_CREEPS,
            .max_health = 100,
            .speed = 200.0f,
            .type = DARK_WIZARD,
            .ability_count = 1,
            .ability_id = {ABILITY_CHAIN_LIGHTNING},
            .comp_mask = (1 << COMPONENT_ABILITY_CASTER),
        },

    [LIGHT_WIZARD] =
        {
            .tag_mask = TAG_PLAYER_CREEPS,
            .max_health = 100,
            .speed = 200.0f,
            .type = LIGHT_WIZARD,
            .ability_count = 2,
            .ability_id = {ABILITY_FIREBALL, ABILITY_CHAIN_LIGHTNING},
            .comp_mask = (1 << COMPONENT_ABILITY_CASTER),
        },

};

int summon_entity_template(World *world, EntityType type, float pos_x, float pos_y)
{
    EntityTemplate entity = entity_template[type];

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag_mask |= entity.tag_mask;

        cPosition p = {.x = pos_x, .y = pos_y};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = entity.speed};

        cSprite entity_sprite = all_entitites_types[type];
        cSprite sprite = {
            .spritesheet = world->sprite_manager.glad_texture,
            .sprite_height = world->sprite_manager.glad_sprite_height,
            .sprite_width = world->sprite_manager.glad_sprite_width,
            .sprite_row = entity_sprite.sprite_row,
            .sprite_col = entity_sprite.sprite_col,
            .direction = entity_sprite.direction,
        };
        cHealth h = {.max_health = entity.max_health, .current_health = entity.max_health};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cAbilityCaster ability_caster;

        if (entity.ability_count > 0) {
            ability_caster.ability_count = entity.ability_count;
            Ability ability[entity.ability_count];
            dictInit(&ability_caster.remaining_cd, entity.ability_count, sizeof(float));
            dictInit(&ability_caster.abilities, entity.ability_count, sizeof(Ability));
            float cd = 0.0f;
            for (int i = 0; i < entity.ability_count; i++) {
                dictAdd(&ability_caster.remaining_cd, entity.ability_id[i], &cd);

                ability[i] = all_abilities[entity.ability_id[i]];
                dictAdd(&ability_caster.abilities, entity.ability_id[i], &ability[i]);

                /*cCastRequest cast_request = {.ability_id = ABILITY_CHAIN_LIGHTNING, .target = 1, .is_active = true};*/
            }
            add_component(world, id, COMPONENT_ABILITY_CASTER, &ability_caster);
        }

        add_component(world, id, COMPONENT_POSITION, &p);
        add_component(world, id, COMPONENT_VELOCITY, &v);
        add_component(world, id, COMPONENT_HEALTH, &h);
        add_component(world, id, COMPONENT_GRIDPOSITION, &g);
        add_component(world, id, COMPONENT_SPRITE, &sprite);
    }

    return id;
}

int summon_enemy_caster(World *world, float pos_x, float pos_y)
{

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag_mask |= TAG_ENEMY_HERO;

        cPosition p = {.x = pos_x, .y = pos_y};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};

        cSprite dark_wizard_sprite = all_entitites_types[DARK_WIZARD];
        cSprite sprite = {
            .spritesheet = world->sprite_manager.glad_texture,
            .sprite_height = world->sprite_manager.glad_sprite_height,
            .sprite_width = world->sprite_manager.glad_sprite_width,
            .sprite_row = dark_wizard_sprite.sprite_row,
            .sprite_col = dark_wizard_sprite.sprite_col,
            .direction = dark_wizard_sprite.direction,
        };
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cPath path = {.length = 0, .current_index = 0, .active = false};
        cTarget target = {
            .current_target = INVALID_ENTITY_ID, .target_distance = 100000, .is_new = true, .is_active = false};
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

int summon_test_entity(World *world, float pos_x, float pos_y)
{

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag_mask |= TAG_PLAYER_CREEPS;

        cPosition p = {.x = pos_x, .y = pos_y};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};
        cSprite sprite = {
            .spritesheet = world->sprite_manager.glad_texture,
            .sprite_height = world->sprite_manager.glad_sprite_height,
            .sprite_width = world->sprite_manager.glad_sprite_width,
            .sprite_row = 0,
            .sprite_col = 3,
            .direction = 1,
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
