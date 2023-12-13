#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

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

    planet_t earth = create_planet(M_EARTH, (vec2){50, 50});

    planet_t planets[1] = {earth};

    system_t solarSytem =
        {
            .star = sun,
            .nb_planets = 1, // because only earth for now
            .planets = planets};
    // ====

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
