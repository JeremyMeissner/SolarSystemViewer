#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

//Planets data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/ (un peu stylé)
//Sun data source : https://nssdc.gsfc.nasa.gov/planetary/factsheet/sunfact.html

//In KG
#define M_SUN 1988500e24
#define M_MOON 0.073e24
#define M_EARTH 5.97e24
#define M_JUPITER 1898e24
#define M_MERCURY 0.330e24
#define M_MARS 0.642e24
#define M_NEPTUNE 102e24

//In KM
#define D_SUN 0
#define D_MOON 0.384e6 //Note that the distance is not from the sun but from the surface of the earth
#define D_EARTH 149.6e6
#define D_JUPITER 778.5e6
#define D_MERCURY 57.9e6
#define D_MARS 228e6
#define D_NEPTUNE 4515e6

//Outer Wilds Mode

/*
Quick guide
Sun = Sun
Moon = Atlerock
Earth = Timber Hearth
Jupiter = Giant's Deep
Mercury = Ash twin
Mars = Brittle Hollow
Neptune = Dark Bramble
*/

//In KG
#define M_SUN 1988500e24
#define M_ATLEROCK 0.073e24
#define M_TIMBER_HEARTH 5.97e24
#define M_GIANTS_DEEP 1898e24
#define M_ASH_TWIN 0.330e24
#define M_BRITTLE_HOLLOW 0.642e24
#define M_DARK_BRAMBLE 102e24

//In KM
#define D_SUN 0
#define D_ALTEROCK 0.384e6 //Note that this distance is not from the sun but from the surface of the timber hearth
#define D_TIMBER_HEARTH 149.6e6
#define D_GIANTS_DEEP 778.5e6
#define D_ASH_TWIN 57.9e6
#define D_BRITTLE_HOLLOW 228e6
#define D_DARK_BRAMBLE 4515e6

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

void show_planet(struct gfx_context_t *ctxt, planet_t planet, bool isSun);
void show_system(struct gfx_context_t *ctxt, system_t system);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);

/*REMOVE THIS*/
//double power_scale(double planet_mass, double smallest_mass, double biggest_mass, double min_output_size, double max_output_size, double power);

#endif