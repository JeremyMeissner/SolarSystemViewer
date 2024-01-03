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

void place_planet(planet_t * planet,double starting_distance_from_sun, int displayWidth, int displayHeight){
    
    //The 0/0 in the solar system is in the top left corner with the sun in the middle being at y and x at the biggest distance possible which is the distance from neptune
    vec2 pos = vec2_create(DISTANCE_NEPTUNE + starting_distance_from_sun + DIAMETER_SUN / 2.0,DISTANCE_NEPTUNE);
    vec2 display_pos = convert_planet_pos_to_display_pos(displayWidth,displayHeight,pos);
    planet->display_pos = display_pos;
    planet->pos = pos;
}

planet_t create_planet(double mass,double diameter)
{
    vec2 startPos = vec2_create(0,0);
    //You an play with the power factor to controll the ratio between the size of the biggest element and the planets
    double power_factor = 0.8;
    double display_diameter = power_scale(diameter,DIAMETER_MOON,DIAMETER_SUN,MIN_DISPLAY_PLANET_SIZE,MAX_DISPLAY_PLANET_SIZE,power_factor);
    return (planet_t){
        .mass = mass,
        .diameter = diameter,
        .display_diameter = display_diameter,
        .pos = startPos,
        .prec_pos = startPos};
}

void show_planet(struct gfx_context_t *ctxt, planet_t planet)
{
    uint32_t color = MAKE_COLOR(255, 0, 255);
    draw_full_circle(ctxt, planet.display_pos.x, planet.display_pos.y, planet.display_diameter, color);
}

vec2 convert_planet_pos_to_display_pos(int displayWidth,int displayHeight,vec2 planet_pos){
    //WE assume that the system cannot be bigger than D_Neptune *2
    double system_size = DISTANCE_NEPTUNE * 2.0;
    double x = (int)power_scale(planet_pos.x,0,system_size,0,displayWidth,1);
    double y = (int)power_scale(planet_pos.y,0,system_size,0,displayHeight,1);
    return vec2_create(x,y);
}

void show_system(struct gfx_context_t *ctxt, system_t system)
{
    //we start at 1 to display only the planet and not the sun
    for (uint32_t i = 1; i < system.nb_planets; i++)
    {
        planet_t planet = system.planets[i];
        system.planets[i].display_pos = convert_planet_pos_to_display_pos(ctxt->width,ctxt->height,planet.pos);
        show_planet(ctxt, planet);
    }
}

void update_system(system_t *system, double delta_t)
{
    //We dont want to affect the sun for now
    for (uint32_t i = 1; i < system->nb_planets; i++)
    {
        system->planets[i].pos.x += 10000;
        system->planets[i].pos.y += 10000;
        //planet.pos = vec2_create(planet.pos.x + 1234, planet.pos.y + 1234);
    }
}

void free_system(system_t *system)
{
    free(system->planets);
}