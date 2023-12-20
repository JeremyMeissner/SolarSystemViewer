#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NBR_PLANETS 4

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

    planet_t sun = create_planet(M_SUN, (vec2){D_SUN_TO_SUN, 0}, SUN_ECCENTRICITY);
    planet_t earth = create_planet(M_EARTH, (vec2){D_EARTH_TO_SUN, 0}, EARTH_ECCENTRICITY);
    planet_t jupiter = create_planet(M_JUPITER, (vec2){D_JUPITER_TO_SUN, 0}, JUPITER_ECCENTRICITY);
    planet_t neptune = create_planet(M_NEPTUNE, (vec2){D_NEPTUNE_TO_SUN, 0}, NEPTUNE_ECCENTRICITY);

    planet_t planets[NBR_PLANETS] = {sun, earth, jupiter, neptune};

    system_t solarSytem =
        {
            .nb_planets = NBR_PLANETS,
            .planets = planets,
        };

    // ====

    initialize_system(&solarSytem);
    while (true)
    {
        gfx_present(ctxt);

        /// ==== Update system here
        gfx_clear(ctxt, COLOR_BLACK);

        // update_system(&solarSytem, 1e9);

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
