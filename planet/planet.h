#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

// Masse
#define M_SUN 1.989e30
#define M_EARTH 5.972e24
#define M_JUPITER 6.39e23
#define M_NEPTUNE 1.024e26

// Distance to sun
#define D_SUN_TO_SUN 0
#define D_EARTH_TO_SUN 149.6e9
#define D_JUPITER_TO_SUN 778.5e9
#define D_NEPTUNE_TO_SUN 4.498e12

// Excentricité orbitale
#define SUN_ECCENTRICITY 0
#define EARTH_ECCENTRICITY 0.0167
#define JUPITER_ECCENTRICITY 0.0484
#define NEPTUNE_ECCENTRICITY 0.00859

// Max distance
#define MAX_DISTANCE D_NEPTUNE_TO_SUN

// Gravitational constant
#define G 6.67e-11

typedef struct _planet
{
    double mass;
    double eccentricity;
    vec2 pos;      // x(t)
    vec2 prec_pos; // x(t - dt)
} planet_t;

typedef struct _system
{
    // planet_t star;       // ex. The sun
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass, vec2 pos, double eccentricity);
system_t create_system(double delta_t);
void show_planet(struct gfx_context_t *ctxt, planet_t planet);
void show_system(struct gfx_context_t *ctxt, system_t system);
void update_system(system_t *system, double delta_t);
void initialize_system(system_t *system);
void free_system(system_t *system);

#endif