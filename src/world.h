#ifndef WORLD_H
#define WORLD_H

#include "event_handler.h"
#include "raylib.h"
#include "stdbool.h"
#include "stdlib.h"

#include "dev_tools/sprite_manager.h"
#include "globals.h"
#include "support/grid.h"

#include "../components/ability.h"
#include "../components/aistate.h"
#include "../components/bounding_rect.h"
#include "../components/grid_position.h"
#include "../components/health.h"
#include "../components/path.h"
#include "../components/position.h"
#include "../components/properties.h"
#include "../components/range.h"
#include "../components/sprite.h"
#include "../components/target.h"
#include "../components/velocity.h"

enum GameState {
    TITLE_SCREEN = 0,
    HUB = 1,
    WAVESETUP = 2,
    GAME_COMBAT = 3,
    ENDGAME = 4,
};

enum MouseState {
    FREE_MOUSE = 0,
    DRAG_HIGHLIGHT = 1,
    SUMMON_SELECT = 2,
};

typedef struct ComponentPool {
    void *data;
    size_t component_size;
    int free_ids[MAX_ENTITIES];
    int free_count;
    int active_count;
} ComponentPool;

typedef struct Keys {
    Vector2 mouse_position;
    float mouse_wheel;
    bool left_click;
    bool right_click;
    bool key_space;
    bool key_shift;
    bool key_a_down;
    bool key_a;
    bool key_w;
    bool key_s;
    bool key_f2;
    bool key_f3;
    int selected_menu_item;
    int selected_unit_id;
} Keys;

typedef struct Debug {
    Elements ele[MAX_ENTITIES];
    bool inpector_toggle_keys;
    bool can_toggle_inspector;
    bool inpector_is_visible;
    Vector2 window_position;
    Vector2 window_size;
    bool minimized;
    bool moving;
    bool resizing;
    Vector2 scroll_threshold;
    Vector2 scroll;
    bool profiler_vis;
    bool AABR_vis;
} Debug;

typedef struct {
    enum GameState game_state;
    bool is_paused;
} GameState;

typedef struct World {
    Entity entities[MAX_ENTITIES];
    int free_ids[MAX_ENTITIES];
    int free_id_count;
    int entity_count;

    cPosition positions[MAX_ENTITIES];
    cGridPosition grid_position[MAX_ENTITIES];
    cSprite sprite[MAX_ENTITIES];
    cVelocity velocities[MAX_ENTITIES];
    cHealth health[MAX_ENTITIES];
    cProperties properties[MAX_ENTITIES];
    cPath path[MAX_ENTITIES];
    cTarget target[MAX_ENTITIES];
    cAIState ai_state[MAX_ENTITIES];
    cBoundingRect bounding_rect[MAX_ENTITIES];
    cHoverRange range[MAX_ENTITIES];

    cAbilityContainer ability_container[MAX_ENTITIES];
    cCastRequest cast_request[MAX_ENTITIES];

    ComponentPool *component_pools;
    GameState game_state;
    enum MouseState mouse_state;
    AdjustableParameters adj_para;

    SpriteManager sprite_manager;
    EventHandler event_handler;
    Event event;

    Keys keys;
    Grid grid;
    Debug debug;
} World;

World *create_world(void);
void destroy_world(World *world);

void add_component(World *world, int entity_id, int component_type, void *component_data);
void remove_component(World *world, int entity_id, int component_type);

cPosition *get_position(World *world, int entity_id);
cVelocity *get_velocity(World *world, int entity_id);
cHealth *get_health(World *world, int entity_id);
cProperties *get_properties(World *world, int entity_id);
cGridPosition *get_grid_position(World *world, int entity_id);
cPath *get_path(World *world, int entity_id);
cTarget *get_target(World *world, int entity_id);
cAIState *get_ai_state(World *world, int entity_id);
cAbilityContainer *get_ability_caster(World *world, int entity_id);
cCastRequest *get_cast_request(World *world, int entity_id);
cSprite *get_sprite(World *world, int entity_id);

#endif
