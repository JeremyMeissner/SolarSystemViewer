#include "planet.h"
#include <stdlib.h>

// TODO : magic

// get max distance for x axis
double get_max_distance(system_t system)
{
    double max_distance = 0;
    for (uint32_t i = 0; i < system.nb_planets; i++)
    {
        planet_t planet = system.planets[i];
        double distance = planet.pos.x;
        if (distance > max_distance)
        {
            max_distance = distance;
        }
    }
    return max_distance;
}

planet_t create_planet(double mass, vec2 pos, double eccentricity)
{
    return (planet_t){
        .mass = mass,
        .eccentricity = eccentricity,
        .pos = pos,
        .prec_pos = pos};
}

void show_planet(struct gfx_context_t *ctxt, planet_t planet)
{

    vec2 coord = vec2_scale_distance_to_screen(planet.pos, ctxt->width, MAX_DISTANCE);

    bool isSun = planet.mass == M_SUN;

    uint32_t color = isSun ? MAKE_COLOR(255, 255, 0) : MAKE_COLOR(0, 0, 255);

    draw_full_circle(ctxt, coord.x, ctxt->height / 2, 2, color);
}

void show_system(struct gfx_context_t *ctxt, system_t system)
{
    for (uint32_t i = 0; i < system.nb_planets; i++)
    {
        planet_t planet = system.planets[i];
        show_planet(ctxt, planet);
    }
}

void initialize_system(system_t *system)
{
    for (uint32_t i = 0; i < system->nb_planets; i++)
    {
        // Calculate the radius (distance from the Sun) as the norm of the position vector
        double rayon = vec2_norm(system->planets[i].pos);

        double acceleration = (G * M_SUN) / pow(rayon, 2);

        // \vec{x_p}(0) = \sqrt{\frac{G * M_SUN * (1 + system->planets[i].eccentricity)}{\vec{a_p}(1- system->planets[i].eccentricity)}} * \frac{system->planets[i].pos}{vec2_norm(system->planets[i].pos)};
        system->planets[i].pos = vec2_mul(sqrt((G * M_SUN * (1 + system->planets[i].eccentricity)) / acceleration * (1 - system->planets[i].eccentricity)), vec2_normalize(system->planets[i].pos));
        system->planets[i].prec_pos = system->planets[i].pos;
    }
}
void update_system(system_t *system, double delta_t)
{
    // Help
    for (uint32_t i = 0; i < system->nb_planets; i++)
    {
        double rayon = vec2_norm(system->planets[i].pos);

        double acceleration = (G * M_SUN) / pow(rayon, 2);

        // Probably wrong becaseut the acceleration should be base on other planest

        // system->planets[i].pos = 2 * system->planets[i].pos - system->planets[i].prec_pos + (pow(delta_t, 2) / 2) * acceleration;
    }
}

void free_system(system_t *system)
{
    free(system->planets);
}