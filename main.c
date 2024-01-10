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

    // If you change this you techincally zoom

    // Includes up to mars
    //vec2 default_system_visible_size = vec2_create(DISTANCE_MARS * 2.5, DISTANCE_MARS * 2.5);
    // Includes up to Jupiter
    vec2 default_system_visible_size = vec2_create(DISTANCE_JUPITER * 2.2,DISTANCE_JUPITER * 2.2);
    // Includes all planets
    //vec2 default_system_visible_size = vec2_create(DISTANCE_PLUTO * 2.2,DISTANCE_PLUTO * 2.2);

    vec2 system_visible_size = default_system_visible_size;
    vec2 camera_offset = vec2_create(0, 0);

    // use most closest color to planet
    planet_t sun = create_planet(MASS_SUN, DIAMETER_SUN, ECCENTRICITY_SUN, SEMI_MAJOR_AXIS_SUN, MAKE_COLOR(255, 255, 0));
    planet_t mercury = create_planet(MASS_MERCURY, DIAMETER_MERCURY, ECCENTRICITY_MERCURY, SEMI_MAJOR_AXIS_MERCURY, MAKE_COLOR(128, 128, 128));
    planet_t venus = create_planet(MASS_VENUS, DIAMETER_VENUS, ECCENTRICITY_VENUS, SEMI_MAJOR_AXIS_VENUS, MAKE_COLOR(255, 255, 204));
    planet_t earth = create_planet(MASS_EARTH, DIAMETER_EARTH, ECCENTRICITY_EARTH, SEMI_MAJOR_AXIS_EARTH, MAKE_COLOR(0, 105, 148));
    planet_t mars = create_planet(MASS_MARS, DIAMETER_MARS, ECCENTRICITY_MARS, SEMI_MAJOR_AXIS_MARS, MAKE_COLOR(188, 39, 50));
    planet_t jupiter = create_planet(MASS_JUPITER, DIAMETER_JUPITER, ECCENTRICITY_JUPITER, SEMI_MAJOR_AXIS_JUPITER, MAKE_COLOR(204, 133, 63));
    planet_t saturn = create_planet(MASS_SATURN, DIAMETER_SATURN, ECCENTRICITY_SATURN, SEMI_MAJOR_AXIS_SATURN, MAKE_COLOR(241, 208, 144));
    planet_t uranus = create_planet(MASS_URANUS, DIAMETER_URANUS, ECCENTRICITY_URANUS, SEMI_MAJOR_AXIS_URANUS, MAKE_COLOR(108, 208, 231));
    planet_t neptune = create_planet(MASS_NEPTUNE, DIAMETER_NEPTUNE, ECCENTRICITY_NEPTUNE, SEMI_MAJOR_AXIS_NEPTUNE, MAKE_COLOR(28, 134, 238));
    planet_t pluto = create_planet(MASS_PLUTO, DIAMETER_PLUTO, ECCENTRICITY_PLUTO, SEMI_MAJOR_AXIS_PLUTO, MAKE_COLOR(169, 169, 169));

    place_planet(&sun, DISTANCE_SUN, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&mercury, DISTANCE_MERCURY, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&venus, DISTANCE_VENUS, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&earth, DISTANCE_EARTH, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&mars, DISTANCE_MARS, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&jupiter, DISTANCE_JUPITER, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&saturn, DISTANCE_SATURN, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&uranus, DISTANCE_URANUS, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&neptune, DISTANCE_NEPTUNE, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);
    place_planet(&pluto, DISTANCE_PLUTO, SCREEN_WIDTH, SCREEN_HEIGHT, system_visible_size);

    planet_t planets[NUMBER_OF_PLANETS] = {sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, pluto};

    system_t solarSystem =
        {
            .nb_planets = NUMBER_OF_PLANETS,
            .planets = planets,
            .system_visible_size = system_visible_size};
    // ====

    /* DEBUG PLAYGROUND START */

    // You can put stuff with printf's here before the simulation starts

    /* DEBUG PLAYGROUND END */
    int current_planet_focus = 0;
    bool needToSnap = true;
    bool needToUpdatePlanetsDiameters = true;

    // initialize_font();
    while (true)
    {
        gfx_present(ctxt);

        /// ==== Update system here
        // gfx_render_text(ctxt, "Hello worl", 50, 50);
        gfx_clear(ctxt, COLOR_BLACK);

        update_system(&solarSystem, 0.1);

        // draw_line(ctxt, 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT, MAKE_COLOR(255, 255, 255));
        show_system(ctxt, solarSystem, camera_offset);
        //printf("Camera offset : %f,%f\n",camera_offset.x,camera_offset.y);

        int camera_increment = 5;
        double zoom_increment = 0.1;

        int pressedKey = gfx_keypressed();
        if (pressedKey == 27)
        { // Assuming 27 is the key code for Escape
            printf("Shutting down the app\n");
            break;
        }
        else
        {
            if (pressedKey != SDLK_UNKNOWN && pressedKey != 27)
            {
                switch (pressedKey)
                {
                case 'U':
                case 'u':
                    //Zoom out by 10%
                    if(solarSystem.system_visible_size.y < default_system_visible_size.y * 100)
                        solarSystem.system_visible_size.x += solarSystem.system_visible_size.x * zoom_increment;
                    if(solarSystem.system_visible_size.y < default_system_visible_size.y * 100)
                        solarSystem.system_visible_size.y += solarSystem.system_visible_size.y * zoom_increment;
                    needToUpdatePlanetsDiameters = true;
                    break;
                case 'J':
                case 'j':
                    if(solarSystem.system_visible_size.x > default_system_visible_size.x / 100)
                        solarSystem.system_visible_size.x -= solarSystem.system_visible_size.x * zoom_increment;
                    if(solarSystem.system_visible_size.y > default_system_visible_size.y / 100)
                        solarSystem.system_visible_size.y -= solarSystem.system_visible_size.y * zoom_increment;
                    needToUpdatePlanetsDiameters = true;
                    break;
                case '0':
                    current_planet_focus = 0;
                    needToSnap = true;
                    break;
                case '1':
                    current_planet_focus = 1;
                    needToSnap = true;
                    break;
                case '2':
                    current_planet_focus = 2;
                    needToSnap = true;
                    break;
                case '3':
                    current_planet_focus = 3;
                    needToSnap = true;
                    break;
                case '4':
                    current_planet_focus = 4;
                    needToSnap = true;
                    break;
                case '5':
                    current_planet_focus = 5;
                    needToSnap = true;
                    break;
                case '6':
                    current_planet_focus = 6;
                    needToSnap = true;
                    break;
                case '7':
                    current_planet_focus = 7;
                    needToSnap = true;
                    break;
                case '8':
                    current_planet_focus = 8;
                    needToSnap = true;
                    break;
                case '9':
                    current_planet_focus = 9;
                    needToSnap = true;
                    break;

                case SDLK_UP:
                case 'W':
                case 'w':
                    // printf("Up key pressed\n");
                    needToSnap = false;
                    camera_offset.y += camera_increment;
                    break;

                case SDLK_DOWN:
                case 'S':
                case 's':
                    // printf("Down key pressed\n");
                    needToSnap = false;
                    camera_offset.y -= camera_increment;
                    break;
                case SDLK_LEFT:
                case 'A':
                case 'a':
                    // printf("Left key pressed\n");
                    needToSnap = false;
                    camera_offset.x += camera_increment;
                    break;
                case SDLK_RIGHT:
                case 'D':
                case 'd':
                    // printf("Right key pressed\n");
                    needToSnap = false;
                    camera_offset.x -= camera_increment;
                    break;
                // Add more cases for other keys as needed
                default:
                    // printf("Unhandled key pressed\n");
                    break;
                }
            }

            if (needToSnap)
            {
                //printf("Planet position: %f,%f\n",planets[current_planet_focus].pos.x,planets[current_planet_focus].pos.y);
                vec2 pos = convert_planet_pos_to_display_pos(SCREEN_WIDTH, SCREEN_HEIGHT, planets[current_planet_focus].pos, solarSystem.system_visible_size, vec2_create(0,0));
                //printf("Planet position: %f,%f\n",pos.x,pos.y);
                //camera_offset = vec2_create(SCREEN_WIDTH / 2 - pos.x, SCREEN_HEIGHT / 2 - pos.y);
                camera_offset = vec2_create(SCREEN_WIDTH / 2 - pos.x,SCREEN_HEIGHT / 2 - pos.y);
            }
            if(needToUpdatePlanetsDiameters){
                needToUpdatePlanetsDiameters = false;

                double ratio = default_system_visible_size.x / solarSystem.system_visible_size.x;
                for(int i = 0; i < NUMBER_OF_PLANETS;i++){
                    printf("ratio: %f\n",ratio);
                    //printf("old : %f",)
                    solarSystem.planets[i].display_diameter = solarSystem.planets[i].original_display_diameter * ratio;
                }
            }
        }
    }

    // free_system(&solarSytem);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
