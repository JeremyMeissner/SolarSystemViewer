#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define NUMBER_OF_PLANETS 5

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

    planet_t sun = create_planet(M_SUN, (vec2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    planet_t ash_twin = create_planet(M_ASH_TWIN, (vec2){(int)((SCREEN_WIDTH / 6.0) * 1.0),50});
    planet_t timber_hearth = create_planet(M_TIMBER_HEARTH, (vec2){(int)((SCREEN_WIDTH / 6.0) * 2.0),50});
    planet_t brittle_hollow = create_planet(M_BRITTLE_HOLLOW, (vec2){(int)((SCREEN_WIDTH / 6.0) * 3.0),50});
    planet_t giants_deep = create_planet(M_GIANTS_DEEP, (vec2){(int)((SCREEN_WIDTH / 6.0) * 4.0),50});
    planet_t dark_bramble = create_planet(M_DARK_BRAMBLE, (vec2){(int)((SCREEN_WIDTH / 6.0) * 5.0),50});

    planet_t planets[NUMBER_OF_PLANETS] = {ash_twin,timber_hearth,brittle_hollow,giants_deep,dark_bramble};

    system_t solarSytem =
        {
            .star = sun,
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
