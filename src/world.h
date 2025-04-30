#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"
#include "stdlib.h"
#include "globals.h"


#include "../components/velocity.h"
#include "../components/position.h"
#include "../components/health.h"
#include "../components/properties.h"


/*Add more components here*/
enum ComponentType {
    COMPONENT_POSITION = 0,
    COMPONENT_VELOCITY = 1,
    COMPONENT_HEALTH = 2,
    COMPONENT_PROPERTIES = 3,
};


enum GameState {
    TITLE_SCREEN = 0,
    HUB = 1,
    WAVESETUP = 2,
    COMBAT = 3,
    ENDGAME = 4
};


typedef struct {
    void* data;
    size_t component_size;
    int free_ids[MAX_ENTITIES];
    int free_count;
    int active_count;
} ComponentPool;


typedef struct {
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


typedef struct {
    Entity entities[MAX_ENTITIES];
    int free_ids[MAX_ENTITIES];
    int free_id_count;
    int entity_count;

    cPosition positions[MAX_ENTITIES];
    cVelocity velocities[MAX_ENTITIES];
    cHealth health[MAX_ENTITIES];
    cProperties properties[MAX_ENTITIES];

    ComponentPool *component_pools;
    GameState game_state;

    Keys keys;
} World;



World *create_world(void);
void destroy_world(World *world);

void add_component(World *world, int entity_id, int component_type, void* component_data);

cPosition* get_position(World *world, int entity_id);
cVelocity* get_velocity(World *world, int entity_id);
cHealth* get_health(World *world, int entity_id);
cProperties* get_properties(World *world, int entity_id);

#endif
