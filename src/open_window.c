/*
** EPITECH PROJECT, 2023
** open_window.c
** File description:
** open a window
*/

#include "window.h"

void print_framerate(void)
{
    static int first = 1;
    static sfClock *clock;
    static int fps = 0;
    if (first == 1) {
        clock = sfClock_create();
        first = 0;
    }
    sfTime elapsed = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed) >= 1) {
        // PRINTF !!!! BANNED 
        printf("%3d FPS \n", fps);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
}

int is_intersecting_circles(sfCircleShape *c1, sfCircleShape *c2)
{
    sfVector2f vector1 = sfCircleShape_getPosition(c1);
    sfVector2f vector2 = sfCircleShape_getPosition(c2);
    float C1r = sfCircleShape_getRadius(c1);
    float C2r = sfCircleShape_getRadius(c2);
    float C1x = vector1.x + C1r;
    float C1y = vector1.y + C1r;
    float C2x = vector2.x + C2r;
    float C2y = vector2.y + C2r;
    if (((C1x - C2x) * (C1x - C2x)) + ((C1y - C2y) * (C1y - C2y)) <=
        ((C1r + C2r) * (C1r + C2r))) {
        sfCircleShape_setFillColor(c1, sfWhite);
        sfCircleShape_setFillColor(c2, sfWhite);
        return 1;
    }
    return 0;
}

static void analyse_events(sfRenderWindow *win, sfEvent *event)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        sfRenderWindow_close(win);
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(win);
    // if (event->type == sfKeyL)
    //     sfRenderWindow_close(win);
    //     // enable/disable hitboxes and areas.
    // if (event->type == sfKeyS)
    //     sfRenderWindow_close(win);
    //     // enable/disable sprites.
}

void while_window_open(sfRenderWindow *win, sfEvent event,
    corner_t **corners)
{
    while (sfRenderWindow_pollEvent(win, &event))
        analyse_events(win, &event);
    // for (int i = 0; circles[i + 1]; i++) {
    //     for (int j = i + 1; circles[j]; j++) {
    //         is_intersecting_circles(circles[i], circles[j]);
    //     }
    // }
    for (int i = 0; corners[i]; i++) {
        for (int j = 0; corners[i]->ac[j]; j++) {
        // sfCircleShape_move(circles[i], (sfVector2f){(rand() % 10) - 5, (rand() % 10) - 5});
            sfRenderWindow_drawSprite(win, corners[i]->ac[j]->sprite, NULL);
            sfRenderWindow_drawRectangleShape(win, corners[i]->ac[j]->hitbox, NULL);
        }
    }
    sfRenderWindow_display(win);
    print_framerate();
}

int open_window(char **array)
{
    sfRenderWindow *win = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
        "My_Radar", sfDefaultStyle, NULL);
    sfEvent event = {0};
    sfTexture *ac_texture = sfTexture_createFromFile("assets/plane.png", NULL);
    sfTexture *bg_texture = sfTexture_createFromFile("assets/bg.jpg", NULL);
    sfSprite *bg = sfSprite_create();
    aircraft_t **all_ac = init_aircrafts_tab(ac_texture, array);
    corner_t **corners = init_corners(all_ac, get_nb_ac(array));

    // free_array(array);
    sfSprite_setTexture(bg, bg_texture, sfTrue);
    sfRenderWindow_setFramerateLimit(win, 60);
    while (sfRenderWindow_isOpen(win)) {
        sfRenderWindow_clear(win, sfBlack);
        sfRenderWindow_drawSprite(win, bg, NULL);
        while_window_open(win, event, corners);
    }
    sfTexture_destroy(ac_texture);
    sfSprite_destroy(bg);
    sfTexture_destroy(bg_texture);
    // my_destroy(win, corners);
    return 0;
}
