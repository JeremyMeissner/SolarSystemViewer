#include "planet.h"
#include <stdlib.h>

#define G 6.67e-11
//Thos two values are used to determin the size of the planets. Have fun and change them to see the effects
#define MAX_DISPLAY_PLANET_SIZE 100
#define MIN_DISPLAY_PLANET_SIZE 5

// TODO : magic

/* One method to scale planets */
double log_planet_scaling(double planet_mass, double smallest_mass, double biggest_mass, double min_output_size, double max_output_size) {
    double log_min = log(smallest_mass);
    double log_max = log(biggest_mass);

    double log_value = log(planet_mass);

    double scaled_value = min_output_size + ((log_value - log_min) / (log_max - log_min)) * (max_output_size - min_output_size);

    return scaled_value;
}
/* An other method that scale plantes with their masses*/
double power_scale(double planet_mass, double smallest_mass, double biggest_mass, double min_output_size, double max_output_size, double power) {
    double scaled_value = min_output_size + pow((planet_mass - smallest_mass) / (biggest_mass - smallest_mass), power) * (max_output_size - min_output_size);
    return scaled_value;
}
/* A method that scales proportionnally values to fit in a specific range (almost impossible to use with scales of planets)*/
double normalize(double value, double min_val, double max_val,double min_range, double max_range) {
    return min_range + ((value - min_val) / (max_val - min_val) * (max_range-min_range));
}

void place_planet(planet_t * planet,double starting_distance_from_sun, int widthOfSystem, int heightOfSystem){
    int avaibleArea = widthOfSystem/2;
    int y = heightOfSystem / 2;
    //We can now place the planets on the same y axis between the sun and the edge of the system
    //int x = (int)normalize(distanceFromSun,0,D_NEPTUNE,avaibleArea,widthOfSystem);
    int x = (int)power_scale(starting_distance_from_sun,0,D_NEPTUNE,avaibleArea,widthOfSystem,0.3);
    vec2 pos = vec2_create(x,y);
    planet->pos = pos;
}

planet_t create_planet(double mass)
{
    vec2 startPos = vec2_create(0,0);
    //You an play with the power factor to controll the ratio between the size of the biggest element and the planets
    double power_factor = 0.25;
    int planetRadius = power_scale(mass,M_MOON,M_SUN,MIN_DISPLAY_PLANET_SIZE,MAX_DISPLAY_PLANET_SIZE,power_factor);
    return (planet_t){
        .mass = mass,
        .radius = planetRadius,
        .pos = startPos,
        .prec_pos = startPos};
}

void show_planet(struct gfx_context_t *ctxt, planet_t planet)
{
    uint32_t color = MAKE_COLOR(255, 0, 255);

    draw_full_circle(ctxt, planet.pos.x, planet.pos.y, planet.radius, color);
}

void show_system(struct gfx_context_t *ctxt, system_t system)
{
    for (uint32_t i = 0; i < system.nb_planets; i++)
    {
        planet_t planet = system.planets[i];
        show_planet(ctxt, planet);
    }
}

void update_system(system_t *system, double delta_t)
{
    for (uint32_t i = 0; i < system->nb_planets; i++)
    {
        planet_t planet = system->planets[i];
        planet.pos = (vec2){planet.pos.x + delta_t, planet.pos.y + delta_t};
    }
}

void free_system(system_t *system)
{
    free(system->planets);
}