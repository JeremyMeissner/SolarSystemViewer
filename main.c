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

    planet_t sun = create_planet(M_SUN);
    planet_t ash_twin = create_planet(M_ASH_TWIN);
    planet_t timber_hearth = create_planet(M_TIMBER_HEARTH);
    planet_t brittle_hollow = create_planet(M_BRITTLE_HOLLOW);
    planet_t giants_deep = create_planet(M_GIANTS_DEEP);
    planet_t dark_bramble = create_planet(M_DARK_BRAMBLE);
    
    //The planets can only be placed after all the planets have been initialized because we need the size of the sun and the farthest one
    place_planet(&sun,D_SUN,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);
    place_planet(&ash_twin,D_ASH_TWIN,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);
    place_planet(&timber_hearth,D_TIMBER_HEARTH,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);
    place_planet(&brittle_hollow,D_BRITTLE_HOLLOW,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);
    place_planet(&giants_deep,D_GIANTS_DEEP,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);
    place_planet(&dark_bramble,D_DARK_BRAMBLE,SCREEN_WIDTH -dark_bramble.radius,SCREEN_HEIGHT);

    planet_t planets[NUMBER_OF_PLANETS] = {sun,ash_twin,timber_hearth,brittle_hollow,giants_deep,dark_bramble};

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

        update_system(&solarSytem, 10);

        show_system(ctxt, solarSytem);

        // ====

        if (gfx_keypressed() == SDLK_ESCAPE)
        {
            break;
        }
    }

    // free_system(&solarSytem);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
