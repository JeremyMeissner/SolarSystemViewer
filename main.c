#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NUMBER_OF_PLANETS 6

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

    planet_t sun = create_planet(MASS_SUN,DIAMETER_SUN,ECCENTRICITY_SUN);
    planet_t mercury = create_planet(MASS_MERCURY,DIAMETER_MERCURY,ECCENTRICITY_MERCURY);
    planet_t earth = create_planet(MASS_EARTH,DIAMETER_EARTH,ECCENTRICITY_EARTH);
    planet_t mars = create_planet(MASS_MARS,DIAMETER_MARS,ECCENTRICITY_MARS);
    planet_t jupiter = create_planet(MASS_JUPITER,DIAMETER_JUPITER,ECCENTRICITY_JUPITER);
    planet_t neptune = create_planet(MASS_NEPTUNE,DIAMETER_NEPTUNE,ECCENTRICITY_NEPTUNE);
    
    place_planet(&sun,DISTANCE_SUN,SCREEN_WIDTH,SCREEN_HEIGHT);
    place_planet(&mercury,DISTANCE_MERCURY,SCREEN_WIDTH,SCREEN_HEIGHT);
    place_planet(&earth,DISTANCE_EARTH,SCREEN_WIDTH,SCREEN_HEIGHT);
    place_planet(&mars,DISTANCE_MARS,SCREEN_WIDTH,SCREEN_HEIGHT);
    place_planet(&jupiter,DISTANCE_JUPITER,SCREEN_WIDTH,SCREEN_HEIGHT);
    place_planet(&neptune,DISTANCE_NEPTUNE,SCREEN_WIDTH,SCREEN_HEIGHT);

    planet_t planets[NUMBER_OF_PLANETS] = {sun,mercury,earth,mars,jupiter,neptune};

    system_t solarSytem =
        {
            .nb_planets = NUMBER_OF_PLANETS,
            .planets = planets};
    // ====


    /* DEBUG PLAYGROUND START */

    // You can put stuff with printf's here before the simulation starts

    /* DEBUG PLAYGROUND END */

    while (true)
    {
        gfx_present(ctxt);

        /// ==== Update system here
        gfx_clear(ctxt, COLOR_BLACK);

        update_system(&solarSytem, 0.1);

        show_system(ctxt, solarSytem);

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
