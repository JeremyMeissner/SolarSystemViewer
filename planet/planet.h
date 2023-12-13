#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

typedef struct _planet
{
    double mass;
    vec2 pos;      // x(t)
    vec2 prec_pos; // x(t - dt)
} planet_t;

typedef struct _system
{
    planet_t star;       // ex. The sun
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass, vec2 pos);
system_t create_system(double delta_t);
void show_system(struct gfx_context_t *ctxt, system_t *system);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);

#endif