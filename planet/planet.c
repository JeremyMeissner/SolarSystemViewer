#include "planet.h"
#include <stdlib.h>

#define G 6.67e-11
//Thos two values are used to determin the size of the planets. Have fun and change them to see the effects
#define MAX_DISPLAY_PLANET_SIZE 100
#define MIN_DISPLAY_PLANET_SIZE 2

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
    vec2 pos = vec2_create(DISTANCE_JUPITER + starting_distance_from_sun + DIAMETER_SUN / 2.0,DISTANCE_JUPITER);
    vec2 display_pos = convert_planet_pos_to_display_pos(displayWidth,displayHeight,pos);
    planet->display_pos = display_pos;
    planet->pos = pos;
}

planet_t create_planet(double mass,double diameter,double eccentricity)
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
        .eccentricity = eccentricity,
        .prec_pos = vec2_create(-1,-1)};
}

void show_planet(struct gfx_context_t *ctxt, planet_t planet)
{
    uint32_t color = MAKE_COLOR(255, 0, 255);
    draw_full_circle(ctxt, planet.display_pos.x, planet.display_pos.y, planet.display_diameter, color);
}

vec2 convert_planet_pos_to_display_pos(int displayWidth,int displayHeight,vec2 planet_pos){
    //WE assume that the system cannot be bigger than D_Neptune *2
    double xRatio = displayWidth / DISTANCE_JUPITER;
    double yRatio = displayHeight / DISTANCE_JUPITER;

    //double system_size = DISTANCE_NEPTUNE * 2;
    //double x = (int)power_scale(planet_pos.x,0,system_size,0,displayWidth,1);
    //double y = (int)power_scale(planet_pos.y,0,system_size,0,displayHeight,1);

    double x = ((planet_pos.x * xRatio) / 2);
    double y = ((planet_pos.y * yRatio) / 2);

    //printf("xRatio: %f\n",xRatio);
    //printf("Value : %f , newValue = %f\n",planet_pos.x,x);
    //printf("Value : %f , newValue = %f\n",planet_pos.y,y);

    //coordinates position = vec2_to_coordinates(planet_pos,displayWidth,displayHeight);
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
    uint32_t color = MAKE_COLOR(255, 255, 0);
    draw_full_circle(ctxt, system.planets[0].display_pos.x, system.planets[0].display_pos.y, 3, color);
}

void update_system(system_t *system, double delta_t)
{
    // Avoid modifying the sun (assuming it's the first element in the array)
    for (uint32_t i = 1; i < system->nb_planets; i++)
    {
        planet_t *planet = &system->planets[i]; // Use pointer to directly modify the planet
        planet_t *sun = &system->planets[0]; // Pointer to the sun for direct access
        /*
        double distance_from_sun = sqrt(pow(planet->pos.x - sun->pos.x, 2) + pow(planet->pos.y - sun->pos.y, 2));

        vec2 diff_sun = vec2_create(planet->pos.x - sun->pos.x, planet->pos.y - sun->pos.y);
        vec2 diff_sun_norm = vec2_normalize(diff_sun);

        //The initial force is the force of the sun
        vec2 F = vec2_mul(G * (MASS_SUN * planet->mass) / pow(distance_from_sun, 2), diff_sun_norm);

        */

        vec2 F = vec2_create(0,0);
        
        for(uint32_t j = 0; j < system->nb_planets; j++){
            //We add the force of the planets
            if(j != i){
                vec2 diff_planet = vec2_create(planet->pos.x - system->planets[j].pos.x, planet->pos.y - system->planets[j].pos.y);
                vec2 diff_planet_norm = vec2_normalize(diff_planet);
                double distance_from_planet = sqrt(pow(planet->pos.x - system->planets[j].pos.x, 2) + pow(planet->pos.y - system->planets[j].pos.y, 2));
                vec2 newF = vec2_mul(G * (system->planets[j].mass * planet->mass) / pow(distance_from_planet, 2), diff_planet_norm);

                F = vec2_add(F,newF);
            }
            
        }

        vec2 ap = vec2_mul(-1 / planet->mass,F); // Force divided by planet's mass gives acceleration

        if (planet->prec_pos.x == -1) 
        {
            //First time
            vec2 Vp_0 = vec2_create(0,0);
            for(uint32_t j =0; j < system->nb_planets; j++){
            //We add the force of the planets
                if(j != i){
                    vec2 diff_planet = vec2_create(planet->pos.x - system->planets[j].pos.x, planet->pos.y - system->planets[j].pos.y);
                    vec2 rp = vec2_create(-diff_planet.y, diff_planet.x);
                    double distance_from_planet = sqrt(pow(planet->pos.x - system->planets[j].pos.x, 2) + pow(planet->pos.y - system->planets[j].pos.y, 2));
                    vec2 Vp_inter = vec2_mul(sqrt(G * system->planets[j].mass * (1 + planet->eccentricity) / (distance_from_planet * (1 - planet->eccentricity))), vec2_normalize(rp));

                    Vp_0 = vec2_add(Vp_0,Vp_inter);
                }
            }
            
            vec2 Xpdtr = vec2_add(vec2_add(planet->pos, vec2_mul(delta_t, Vp_0)), vec2_mul(0.5*pow(delta_t, 2), ap));
            planet->prec_pos = planet->pos;
            planet->pos = Xpdtr;

            printf("\n old/new\n");
            vec2_print(planet->prec_pos);
            printf("VS \n");
            vec2_print(Xpdtr);
        } 
        else 
        {
            vec2 Xptdr = vec2_add(vec2_sub(vec2_mul(2,planet->pos),planet->prec_pos) , vec2_mul(pow(delta_t,2),ap));

            planet->prec_pos = planet->pos;
            planet->pos = Xptdr;
        }
    }
}

void free_system(system_t *system)
{
    free(system->planets);
}