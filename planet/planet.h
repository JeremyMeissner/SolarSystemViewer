#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

//Planets data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/ (un peu stylé)
//Sun data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html

//In KG
#define MASS_SUN 1988500e24
#define MASS_MOON 0.073e24
#define MASS_EARTH 5.97e24
#define MASS_JUPITER 1898e24
#define MASS_MERCURY 0.330e24
#define MASS_MARS 0.642e24
#define MASS_NEPTUNE 102e24

//In KM
#define DISTANCE_SUN 0
#define DISTANCE_MOON 0.384e6 //Note that the distance is not from the sun but from the surface of the earth
#define DISTANCE_EARTH 149.6e6
#define DISTANCE_JUPITER 778.5e6
#define DISTANCE_MERCURY 57.9e6
#define DISTANCE_MARS 228e6
#define DISTANCE_NEPTUNE 4515e6

//In KM
#define DIAMETER_SUN 1392700
#define DIAMETER_MOON 3475
#define DIAMETER_EARTH 12756
#define DIAMETER_JUPITER 142984
#define DIAMETER_MERCURY 4879
#define DIAMETER_MARS 6792
#define DIAMETER_NEPTUNE 49528

typedef struct _planet
{
    double mass;
    double diameter;
    double display_diameter;
    vec2 display_pos;
    vec2 pos;      // x(t)
    vec2 prec_pos; // x(t - dt)
} planet_t;

typedef struct _system
{
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass,double diameter);
system_t create_system(double delta_t);

void show_planet(struct gfx_context_t *ctxt, planet_t planet);
void show_system(struct gfx_context_t *ctxt, system_t system);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);
void place_planet(planet_t * planet,double starting_distance_from_sun, int widthOfSystem, int heightOfSystem);
vec2 convert_planet_pos_to_display_pos(int displayWidth,int displayHeight,vec2 planetPos);

#endif