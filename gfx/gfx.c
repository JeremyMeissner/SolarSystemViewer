/// @file gfx.c
/// @author Florent Gluck
/// @date November 6, 2016
/// Helper routines to render pixels in fullscreen graphic mode.
/// Uses the SDL2 library.
/// Update : Add full circle
/// @author Michaël El Kharroubi
/// @date 19 November 2021

#include "gfx.h"
#include <assert.h>

/// Create a fullscreen graphic window.
/// @param title Title of the window.
/// @param width Width of the window in pixels.
/// @param height Height of the window in pixels.
/// @return a pointer to the graphic context or NULL if it failed.
struct gfx_context_t *gfx_create(char *title, uint32_t width, uint32_t height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        goto error;
    }

    // if (TTF_Init() == -1)
    // {
    //     fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
    //     goto error;
    // }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING, width, height);
    uint32_t *pixels = malloc(width * height * sizeof(uint32_t));
    struct gfx_context_t *ctxt = malloc(sizeof(struct gfx_context_t));

    if (!window || !renderer || !texture || !pixels || !ctxt)
        goto error;

    ctxt->renderer = renderer;
    ctxt->texture = texture;
    ctxt->window = window;
    // ctxt->font = TTF_OpenFont("fonts/Roboto.ttf", 12);
    // ctxt->textColor = (SDL_Color){0, 255, 255};
    ctxt->width = width;
    ctxt->height = height;
    ctxt->pixels = pixels;

    // if (!ctxt->font)
    // {
    //     fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
    //     goto error;
    // }
    SDL_ShowCursor(SDL_DISABLE);
    gfx_clear(ctxt, COLOR_BLACK);
    return ctxt;

error:
    return NULL;
}

// void gfx_render_text(struct gfx_context_t *ctxt, const char *text, int x, int y)
// {
//     SDL_Surface *surface = TTF_RenderText_Solid(ctxt->font, text, ctxt->textColor);
//     if (!surface)
//     {
//         fprintf(stderr, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
//         return;
//     }

//     SDL_Texture *texture = SDL_CreateTextureFromSurface(ctxt->renderer, surface);
//     if (!texture)
//     {
//         fprintf(stderr, "CreateTextureFromSurface Error: %s\n", SDL_GetError());
//         SDL_FreeSurface(surface);
//         return;
//     }

//     SDL_Rect textRect = {x, y, surface->w, surface->h};
//     SDL_RenderCopy(ctxt->renderer, texture, NULL, &textRect);

//     SDL_RenderPresent(ctxt->renderer); // Update the screen with rendered text

//     SDL_FreeSurface(surface);
//     SDL_DestroyTexture(texture);
// }

/// Draw a pixel in the specified graphic context.
/// @param ctxt Graphic context where the pixel is to be drawn.
/// @param column X coordinate of the pixel.
/// @param row Y coordinate of the pixel.
/// @param color Color of the pixel.
void gfx_putpixel(struct gfx_context_t *ctxt, uint32_t column, uint32_t row, uint32_t color)
{
    if (column < ctxt->width && row < ctxt->height)
        ctxt->pixels[ctxt->width * row + column] = color;
}

/// Clear the specified graphic context.
/// @param ctxt Graphic context to clear.
/// @param color Color to use.
void gfx_clear(struct gfx_context_t *ctxt, uint32_t color)
{
    int n = ctxt->width * ctxt->height;
    while (n)
        ctxt->pixels[--n] = color;
}

/// Display the graphic context.
/// @param ctxt Graphic context to clear.
void gfx_present(struct gfx_context_t *ctxt)
{
    SDL_UpdateTexture(
        ctxt->texture, NULL, ctxt->pixels, ctxt->width * sizeof(uint32_t));
    SDL_RenderCopy(ctxt->renderer, ctxt->texture, NULL, NULL);
    SDL_RenderPresent(ctxt->renderer);
}

/// Destroy a graphic window.
/// @param ctxt Graphic context of the window to close.
void gfx_destroy(struct gfx_context_t *ctxt)
{
    SDL_ShowCursor(SDL_ENABLE);
    SDL_DestroyTexture(ctxt->texture);
    SDL_DestroyRenderer(ctxt->renderer);
    SDL_DestroyWindow(ctxt->window);
    free(ctxt->pixels);
    ctxt->texture = NULL;
    ctxt->renderer = NULL;
    ctxt->window = NULL;
    ctxt->pixels = NULL;
    SDL_Quit();
    free(ctxt);
}

/// If a key was pressed, returns its key code (non blocking call).
/// List of key codes: https://wiki.libsdl.org/SDL_Keycode
/// @return the key that was pressed or 0 if none was pressed.
SDL_Keycode gfx_keypressed()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    }
    return 0;
}

/// Draw a full circle using Andres's discrete circle algorithm.
/// @param ctxt Graphic context to clear.
/// @param c_column X coordinate of the circle center.
/// @param c_row Y coordinate of the circle center.
/// @param r The radius of circle (in pixels).
/// @param color Color to use.
void draw_full_circle(struct gfx_context_t *ctxt, uint32_t c_column, uint32_t c_row, uint32_t r, uint32_t color)
{
    int32_t x = 0, y = r, d = r - 1;
    while (y >= x)
    {
        gfx_putpixel(ctxt, c_column + x, c_row + y, color);
        gfx_putpixel(ctxt, c_column + y, c_row + x, color);
        gfx_putpixel(ctxt, c_column - x, c_row + y, color);
        gfx_putpixel(ctxt, c_column - y, c_row + x, color);

        gfx_putpixel(ctxt, c_column + x, c_row - y, color);
        gfx_putpixel(ctxt, c_column + y, c_row - x, color);
        gfx_putpixel(ctxt, c_column - x, c_row - y, color);
        gfx_putpixel(ctxt, c_column - y, c_row - x, color);

        if ((2 * x) <= d)
        {
            d -= 2 * x + 1;
            x += 1;
        }
        else if (d < (2 * (((int32_t)r) - y)))
        {
            d += 2 * y - 1;
            y -= 1;
        }
        else
        {
            d -= 2 * (x - y + 1);
            y -= 1;
            x += 1;
        }
    }
    if (r > 0)
        draw_full_circle(ctxt, c_column, c_row, r - 1, color);
}