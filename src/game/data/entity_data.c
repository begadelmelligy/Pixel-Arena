#include "entity_data.h"
#include "../../ecs_core/entity.h"
#include "ability_data.h"
#include "raylib.h"
#include <stdio.h>

EntityTemplate entity_template[ENTITY_TYPE_COUNT] = {
    [DARK_WIZARD] =
        {
            (cSprite){
                .sprite_row = 2,
                .sprite_col = 5,
                .direction = 1,
            },
            .bb_x_scale = 1,
            .bb_y_scale = 1,
            .sprite_sheet_type = SHEET_GLADIATORS,
            .tag = TAG_PLAYER_CREEPS,
            .tag_mask = (1 << TAG_PLAYER_CREEPS),
            .max_health = 100,
            .speed = 200.0f,
            .ability_count = 1,
            .ability_id = {ABILITY_CHAIN_LIGHTNING},
            .comp_mask = (1 << COMPONENT_ABILITY_CONTAINER),
        },

    [LIGHT_WIZARD] =
        {
            (cSprite){
                .sprite_row = 2,
                .sprite_col = 6,
                .direction = 1,
            },
            .bb_x_scale = 0.5,
            .bb_y_scale = 1,
            .sprite_sheet_type = SHEET_GLADIATORS,
            .tag = TAG_PLAYER_CREEPS,
            .tag_mask = (1 << TAG_PLAYER_CREEPS),
            .max_health = 100,
            .speed = 200.0f,
            .ability_count = 1,
            .ability_id = {ABILITY_FIREBALL},
            .comp_mask = (1 << COMPONENT_ABILITY_CONTAINER),
        },
    [BLUE_ANGEL] =
        {
            (cSprite){
                .sprite_row = 11,
                .sprite_col = 0,
                .direction = 1,
            },
            .bb_x_scale = 1,
            .bb_y_scale = 1,
            .sprite_sheet_type = SHEET_MONSTERS,
            .tag = TAG_PLAYER_CREEPS,
            .tag_mask = (1 << TAG_PLAYER_CREEPS),
            .max_health = 1000,
            .speed = 500.0f,
            .ability_count = 2,
            .ability_id = {ABILITY_FIREBALL, ABILITY_CHAIN_LIGHTNING},
            .comp_mask = (1 << COMPONENT_ABILITY_CONTAINER),
        },

};

int summon_entity_template(World *world, EntityType type, float pos_x, float pos_y)
{
    EntityTemplate entity = entity_template[type];
    SpriteSheetData sprite_sheet_data = get_sprite_sheet(&world->sprite_manager, entity.sprite_sheet_type);

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag = entity.tag;
        world->entities[id].tag_mask = entity.tag_mask;

        cSprite sprite = {
            .sprite_sheet_data.sprite_sheet = sprite_sheet_data.sprite_sheet,
            .sprite_sheet_data.sprite_height = sprite_sheet_data.sprite_height,
            .sprite_sheet_data.sprite_width = sprite_sheet_data.sprite_width,
            .sprite_row = entity.sprite.sprite_row,
            .sprite_col = entity.sprite.sprite_col,
            .direction = entity.sprite.direction,
            .sprite_multi = 3,
        };
        cPosition p = {.x = pos_x, .y = pos_y};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = entity.speed};
        cHealth h = {.max_health = entity.max_health, .current_health = entity.max_health};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cTarget target = {.current_target = INVALID_ENTITY_ID, .target_distance = 100000, .is_new = true, .is_active = false};
        cAIState state = {.current_state = STATE_IDLE, .next_state = STATE_EMPTY};
        cAbilityContainer ability_container = {.ability_count = entity.ability_count, .is_casting = false, .remaining_cast_time = 0};
        cCastRequest cast_request = {.ability_id = ABILITY_NONE, .target = INVALID_ENTITY_ID, .is_active = false};
        cBoundingRect bounding_rect = {
            .rect =
                (Rectangle){
                    pos_x - ((float)sprite_sheet_data.sprite_width * sprite.sprite_multi / 2) * entity.bb_x_scale,
                    pos_y - ((float)sprite_sheet_data.sprite_height * sprite.sprite_multi / 2) * entity.bb_y_scale,
                    ((float)sprite_sheet_data.sprite_width * sprite.sprite_multi) * entity.bb_x_scale,
                    ((float)sprite_sheet_data.sprite_height * sprite.sprite_multi) * entity.bb_y_scale,
                },
            .is_visible = true};

        if (entity.ability_count > 0) {
            Ability ability[entity.ability_count];
            dictInit(&ability_container.remaining_cd, entity.ability_count, sizeof(float));
            dictInit(&ability_container.abilities, entity.ability_count, sizeof(Ability));
            for (int i = 0; i < entity.ability_count; i++) {
                float cd = 0.0f;
                dictAdd(&ability_container.remaining_cd, entity.ability_id[i], &cd);

                ability[i] = all_abilities[entity.ability_id[i]];
                dictAdd(&ability_container.abilities, entity.ability_id[i], &ability[i]);
            }
            add_component(world, id, COMPONENT_ABILITY_CONTAINER, &ability_container);
            add_component(world, id, COMPONENT_CAST_REQUEST, &cast_request);
        }

        add_component(world, id, COMPONENT_POSITION, &p);
        add_component(world, id, COMPONENT_VELOCITY, &v);
        add_component(world, id, COMPONENT_HEALTH, &h);
        add_component(world, id, COMPONENT_GRIDPOSITION, &g);
        add_component(world, id, COMPONENT_TARGET, &target);
        add_component(world, id, COMPONENT_AISTATE, &state);
        add_component(world, id, COMPONENT_SPRITE, &sprite);
        add_component(world, id, COMPONENT_BOUNDING_RECT, &bounding_rect);
    }
    return id;
}

int summon_enemy_caster(World *world, float pos_x, float pos_y)
{

    int id = create_entity(world);
    if (id != INVALID_ENTITY_ID) {
        world->entities[id].tag = TAG_ENEMY_HERO;
        world->entities[id].tag_mask = (1 << TAG_ENEMY_HERO);

        cPosition p = {.x = pos_x, .y = pos_y};
        cVelocity v = {.dx = 0.f, .dy = 0.f, .speed = 200.0f};

        EntityTemplate dark_wizard = entity_template[DARK_WIZARD];
        SpriteSheetData sprite_sheet_data = get_sprite_sheet(&world->sprite_manager, dark_wizard.sprite_sheet_type);
        cSprite sprite = {
            .sprite_sheet_data.sprite_sheet = sprite_sheet_data.sprite_sheet,
            .sprite_sheet_data.sprite_height = sprite_sheet_data.sprite_height,
            .sprite_sheet_data.sprite_width = sprite_sheet_data.sprite_width,
            .sprite_row = dark_wizard.sprite.sprite_row,
            .sprite_col = dark_wizard.sprite.sprite_col,
            .direction = dark_wizard.sprite.direction,
            .sprite_multi = 3,
        };
        cHealth h = {.max_health = 100, .current_health = 100};
        cGridPosition g = {.x = p.x / CELL_SIZE, .y = p.y / CELL_SIZE};
        cPath path = {.length = 0, .current_index = 0, .active = false};
        cTarget target = {.current_target = INVALID_ENTITY_ID, .target_distance = 100000, .is_new = true, .is_active = false};
        cAIState state = {.current_state = STATE_IDLE, .next_state = STATE_EMPTY};
        cAbilityContainer ability_container = {.ability_count = 1, .is_casting = false, .remaining_cast_time = 0};
        cCastRequest cast_request = {.ability_id = ABILITY_NONE, .target = 1, .is_active = false};
        cBoundingRect bounding_rect = {
            .rect =
                (Rectangle){
                    pos_x - ((float)sprite_sheet_data.sprite_width * sprite.sprite_multi / 2) * dark_wizard.bb_x_scale,
                    pos_y - ((float)sprite_sheet_data.sprite_height * sprite.sprite_multi / 2) * dark_wizard.bb_y_scale,
                    ((float)sprite_sheet_data.sprite_width * sprite.sprite_multi) * dark_wizard.bb_x_scale,
                    ((float)sprite_sheet_data.sprite_height * sprite.sprite_multi) * dark_wizard.bb_y_scale,
                },
            .is_visible = true};

        float cd = 0.0f;
        dictInit(&ability_container.remaining_cd, ability_container.ability_count, sizeof(float));
        dictAdd(&ability_container.remaining_cd, ABILITY_CHAIN_LIGHTNING, &cd);
        /*dictAdd(&ability_container.remaining_cd, ABILITY_FIREBALL, &cd);*/

        Ability ability1 = all_abilities[ABILITY_CHAIN_LIGHTNING];
        /*Ability ability2 = all_abilities[ABILITY_FIREBALL];*/
        dictInit(&ability_container.abilities, ability_container.ability_count, sizeof(Ability));
        dictAdd(&ability_container.abilities, ABILITY_CHAIN_LIGHTNING, &ability1);
        /*dictAdd(&ability_container.abilities, ABILITY_FIREBALL, &ability2);*/

        add_component(world, id, COMPONENT_POSITION, &p);
        add_component(world, id, COMPONENT_VELOCITY, &v);
        add_component(world, id, COMPONENT_HEALTH, &h);
        add_component(world, id, COMPONENT_GRIDPOSITION, &g);
        add_component(world, id, COMPONENT_PATH, &path);
        add_component(world, id, COMPONENT_TARGET, &target);
        add_component(world, id, COMPONENT_AISTATE, &state);
        add_component(world, id, COMPONENT_ABILITY_CONTAINER, &ability_container);
        add_component(world, id, COMPONENT_CAST_REQUEST, &cast_request);
        add_component(world, id, COMPONENT_SPRITE, &sprite);
        add_component(world, id, COMPONENT_BOUNDING_RECT, &bounding_rect);
    }

    return id;
}
