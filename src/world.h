#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"
#include "stdlib.h"
#include <math.h>

#include "globals.h"
#include "grid.h"

#include "../components/aistate.h"
#include "../components/grid_position.h"
#include "../components/health.h"
#include "../components/path.h"
#include "../components/position.h"
#include "../components/properties.h"
#include "../components/target.h"
#include "../components/velocity.h"

enum GameState { TITLE_SCREEN = 0, HUB = 1, WAVESETUP = 2, GAME_COMBAT = 3, ENDGAME = 4 };

typedef struct ComponentPool {
    void *data;
    size_t component_size;
    int free_ids[MAX_ENTITIES];
    int free_count;
    int active_count;
} ComponentPool;

typedef struct Keys {
    Vector2 mouse_position;
    bool left_click;
    bool right_click;
    bool key_space;
    bool key_shift;
    int selected_menu_item;
    int selected_unit_id;
} Keys;

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
    cVelocity velocities[MAX_ENTITIES];
    cHealth health[MAX_ENTITIES];
    cProperties properties[MAX_ENTITIES];
    cGridPosition grid_position[MAX_ENTITIES];
    cPath path[MAX_ENTITIES];
    cTarget target[MAX_ENTITIES];
    cAIState ai_state[MAX_ENTITIES];

    ComponentPool *component_pools;
    GameState game_state;

    Keys keys;
    Grid grid;
} World;

World *create_world(void);
void destroy_world(World *world);

void add_component(World *world, int entity_id, int component_type, void *component_data);

cPosition *get_position(World *world, int entity_id);
cVelocity *get_velocity(World *world, int entity_id);
cHealth *get_health(World *world, int entity_id);
cProperties *get_properties(World *world, int entity_id);
cGridPosition *get_grid_position(World *world, int entity_id);
cPath *get_path(World *world, int entity_id);
cTarget *get_target(World *world, int entity_id);
cAIState *get_ai_state(World *world, int entity_id);

#endif
