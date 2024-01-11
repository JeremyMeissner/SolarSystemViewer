#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

// Planets data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/ (un peu stylé)
// Sun data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html

// In KG
#define MASS_SUN 1988500e24
#define MASS_MERCURY 0.330e24
#define MASS_MOON 0.073e24
#define MASS_EARTH 5.97e24
#define MASS_JUPITER 1898e24
#define MASS_MARS 0.642e24
#define MASS_NEPTUNE 102e24
#define MASS_VENUS 4.87e24
#define MASS_PLUTO 0.0130e24
#define MASS_SATURN 568e24
#define MASS_URANUS 86.8e24

// Distance from sun at perihelion in KM
#define DISTANCE_SUN 0
#define DISTANCE_MERCURY 46e6
#define DISTANCE_VENUS 107e6
#define DISTANCE_EARTH 147e6
#define DISTANCE_MARS 206e6
#define DISTANCE_JUPITER 740e6
#define DISTANCE_SATURN 1350e6
#define DISTANCE_URANUS 2740e6
#define DISTANCE_NEPTUNE 4450e6
#define DISTANCE_PLUTO 7375e6

// In KM
#define DIAMETER_SUN 1392700
#define DIAMETER_MERCURY 4879
#define DIAMETER_VENUS 12104
#define DIAMETER_EARTH 12756
#define DIAMETER_MOON 3475
#define DIAMETER_MARS 6792
#define DIAMETER_JUPITER 142984
#define DIAMETER_SATURN 120536
#define DIAMETER_URANUS 51118
#define DIAMETER_NEPTUNE 49528
#define DIAMETER_PLUTO 2376

#define ECCENTRICITY_SUN 0
#define ECCENTRICITY_MERCURY 0.206
#define ECCENTRICITY_VENUS 0.007
#define ECCENTRICITY_EARTH 0.017
#define ECCENTRICITY_MARS 0.094
#define ECCENTRICITY_JUPITER 0.049
#define ECCENTRICITY_SATURN 0.052
#define ECCENTRICITY_URANUS 0.047
#define ECCENTRICITY_NEPTUNE 0.010
#define ECCENTRICITY_PLUTO 0.244

// Semi Major Axis
#define SEMI_MAJOR_AXIS_SUN 0
#define SEMI_MAJOR_AXIS_MERCURY 57.9e6
#define SEMI_MAJOR_AXIS_VENUS 108.2e6
#define SEMI_MAJOR_AXIS_EARTH 149.6e6
#define SEMI_MAJOR_AXIS_MARS 228e6
#define SEMI_MAJOR_AXIS_JUPITER 778.5e6
#define SEMI_MAJOR_AXIS_SATURN 1432e6
#define SEMI_MAJOR_AXIS_URANUS 2867e6
#define SEMI_MAJOR_AXIS_NEPTUNE 4515e6
#define SEMI_MAJOR_AXIS_PLUTO 5906.4e6

typedef struct _planet
{
    double mass;
    double diameter;
    double original_display_diameter;
    double display_diameter;
    double eccentricity;
    double semi_major_axis;
    uint32_t color;
    vec2 *all_prev_pos;
    int all_prev_pos_index;
    vec2 display_pos;
    vec2 pos;      // x(t)
    vec2 prec_pos; // x(t - dt)
    // double all_prec_pos_index;
} planet_t;

// typedef struct _previous_pos
// {

// } previous_pos_t

typedef struct _system
{
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
    vec2 system_visible_size;
} system_t;

// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass, double diameter, double eccentricity, double semi_major_axis, uint32_t color);
system_t create_system(double delta_t, vec2 visible_system_size);

void show_planet(struct gfx_context_t *ctxt, planet_t planet, int planetID);
void toggle_realist_mode(bool realist, system_t* system);
void show_system(struct gfx_context_t *ctxt, system_t system, vec2 camera_offset);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);
void place_planet(planet_t *planet, double starting_distance_from_sun, int widthOfSystem, int heightOfSystem, vec2 system_size);
vec2 convert_planet_pos_to_display_pos(int displayWidth, int displayHeight, vec2 planetPos, vec2 system_size, vec2 camera_offset);
void save_pos_history(planet_t *planet);
void show_pos_history_with_lines(system_t system, struct gfx_context_t *ctxt, vec2 camera_offset);

#endif