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

    // TODO : create your system

    int i = 0;

    while (true)
    {
        gfx_present(ctxt);
        // TODO : draw the current state of your system
        gfx_clear(ctxt, COLOR_BLACK);

        draw_full_circle(ctxt, 50 + i, 50 + i, 50, MAKE_COLOR(255, 0, 0));

        i = i + 50;

        // TODO : update your system
        if (gfx_keypressed() == SDLK_ESCAPE)
        {
            break;
        }
        if (i >= SCREEN_HEIGHT)
        {
            i = 0;
        }
    }

    // TODO : Free your system
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
