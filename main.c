#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NUMBER_OF_PLANETS 10

int main()
{
    srand(time(NULL));
    struct gfx_context_t *ctxt =
        gfx_create("Planetary system", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    // ==== Create system here

    //If you change this you techincally zoom

    //Includes up to mars
    vec2 system_visible_size = vec2_create(DISTANCE_MARS * 2.5,DISTANCE_MARS *2.5);
    //Includes all planets
    //Includes up to Jupiter
    //vec2 system_visible_size = vec2_create(DISTANCE_JUPITER * 2.2,DISTANCE_JUPITER *2.2);
    //Includes all planets
    //vec2 system_visible_size = vec2_create(DISTANCE_PLUTO * 2.2,DISTANCE_PLUTO * 2.2);

    vec2 camera_offset = vec2_create(0,0);


    planet_t sun = create_planet(MASS_SUN,DIAMETER_SUN,ECCENTRICITY_SUN);
    planet_t mercury = create_planet(MASS_MERCURY,DIAMETER_MERCURY,ECCENTRICITY_MERCURY);
    planet_t venus = create_planet(MASS_VENUS,DIAMETER_VENUS,ECCENTRICITY_VENUS);
    planet_t earth = create_planet(MASS_EARTH,DIAMETER_EARTH,ECCENTRICITY_EARTH);
    planet_t mars = create_planet(MASS_MARS,DIAMETER_MARS,ECCENTRICITY_MARS);
    planet_t jupiter = create_planet(MASS_JUPITER,DIAMETER_JUPITER,ECCENTRICITY_JUPITER);
    planet_t saturn = create_planet(MASS_SATURN,DIAMETER_SATURN,ECCENTRICITY_SATURN);
    planet_t uranus = create_planet(MASS_URANUS,DIAMETER_URANUS,ECCENTRICITY_URANUS);
    planet_t neptune = create_planet(MASS_NEPTUNE,DIAMETER_NEPTUNE,ECCENTRICITY_NEPTUNE);
    planet_t pluto = create_planet(MASS_PLUTO,DIAMETER_PLUTO,ECCENTRICITY_PLUTO);
   
    
    place_planet(&sun,DISTANCE_SUN,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&mercury,DISTANCE_MERCURY,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&venus,DISTANCE_VENUS,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&earth,DISTANCE_EARTH,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&mars,DISTANCE_MARS,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&jupiter,DISTANCE_JUPITER,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&saturn,DISTANCE_SATURN,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&uranus,DISTANCE_URANUS,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&neptune,DISTANCE_NEPTUNE,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);
    place_planet(&pluto,DISTANCE_PLUTO,SCREEN_WIDTH,SCREEN_HEIGHT,system_visible_size);

    planet_t planets[NUMBER_OF_PLANETS] = {sun,mercury,venus,earth,mars,jupiter,saturn,uranus,neptune,pluto};

    system_t solarSystem =
        {
            .nb_planets = NUMBER_OF_PLANETS,
            .planets = planets,
            .system_visible_size = system_visible_size};
    // ====


    /* DEBUG PLAYGROUND START */

    // You can put stuff with printf's here before the simulation starts

    /* DEBUG PLAYGROUND END */

    while (true)
    {
        gfx_present(ctxt);

        /// ==== Update system here
        gfx_clear(ctxt, COLOR_BLACK);

        //solarSystem.system_visible_size.x -= 500000;
        //solarSystem.system_visible_size.y -= 500000;

        camera_offset.x -= 0.1;
        camera_offset.y -= 0.1;
        //solarSystem.system_visible_size.x += 500000;
        //solarSystem.system_visible_size.y += 500000;

        update_system(&solarSystem, 0.1);

        show_system(ctxt, solarSystem,camera_offset);

        if (gfx_keypressed() == SDLK_ESCAPE)
        {
            printf("Shutting down the app");
            break;
        }else{
            //Does not work I dont understand how keypresses are supposed to be handled with this lib
            if(gfx_keypressed() == SDLK_SPACE){
                printf("AAAAAAaaaaAAAaAAaAAA");
            }
        }
    }

    // free_system(&solarSytem);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
