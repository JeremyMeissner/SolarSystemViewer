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

planet_t create_planet(double mass, vec2 pos)
{
    return (planet_t){
        .mass = mass,
        .pos = pos,
        .prec_pos = pos};
}

void show_planet(struct gfx_context_t *ctxt, planet_t planet, bool isStar)
{
    uint32_t color = isStar ? MAKE_COLOR(255, 255, 0) : MAKE_COLOR(0, 0, 255);

    //You an play with the power factor to controll the ratio between the size of the biggest element and the planets
    double power_factor = 0.25;
    //This computation should only happen at the start but its here for now
    double planet_size = power_scale(planet.mass,M_MOON,M_SUN,MIN_DISPLAY_PLANET_SIZE,MAX_DISPLAY_PLANET_SIZE,power_factor);
    uint32_t radius = (int)planet_size;

    draw_full_circle(ctxt, planet.pos.x, planet.pos.y, radius, color);
}

void show_system(struct gfx_context_t *ctxt, system_t system)
{
    show_planet(ctxt, system.star, true);

    for (uint32_t i = 0; i < system.nb_planets; i++)
    {
        planet_t planet = system.planets[i];
        show_planet(ctxt, planet, false);
    }
}

void update_system(system_t *system, double delta_t)
{
    // Help
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