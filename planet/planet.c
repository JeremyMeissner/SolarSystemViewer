#include "planet.h"
#include <stdlib.h>

#define G 6.67e-11

// TODO : magic

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

    uint32_t radius = isStar ? 100 : 30;

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