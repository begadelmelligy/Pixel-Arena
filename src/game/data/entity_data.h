#ifndef ENTITY_DATA_H
#define ENTITY_DATA_H

#include "../../world.h"
#include "ability_data.h"

#define ENTITY_TYPE_COUNT 4
#define MAX_ABILITIES_TEMPLATE 4

typedef enum EntityType {
    LIGHT_WIZARD = 0,
    DARK_WIZARD = 1,
    BLUE_ANGEL = 2,
} EntityType;

typedef struct EntityTemplate {
    cSprite sprite;
    enum SpriteSheetType sprite_sheet_type;
    int tag_mask;
    float speed;
    float max_health;
    int ability_count;
    AbilityID ability_id[MAX_ABILITIES_TEMPLATE];
    ComponentMask comp_mask;
} EntityTemplate;

extern EntityTemplate entity_template[ENTITY_TYPE_COUNT];

int summon_entity_template(World *world, EntityType type, float pos_x, float pos_y);
int summon_enemy_caster(World *world, float pos_x, float pos_y);

#endif
