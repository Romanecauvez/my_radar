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
    sfTime elapsed = {0};

    if (first == 1) {
        clock = sfClock_create();
        first = 0;
    }
    elapsed = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed) >= 1) {
        // PRINTF !!!! BANNED
        printf("%3d FPS \n", fps);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
}

// int is_intersecting_circles(sfCircleShape *c1, sfCircleShape *c2)
// {
//     sfVector2f vector1 = sfCircleShape_getPosition(c1);
//     sfVector2f vector2 = sfCircleShape_getPosition(c2);
//     float C1r = sfCircleShape_getRadius(c1);
//     float C2r = sfCircleShape_getRadius(c2);
//     float C1x = vector1.x + C1r;
//     float C1y = vector1.y + C1r;
//     float C2x = vector2.x + C2r;
//     float C2y = vector2.y + C2r;
//     if (((C1x - C2x) * (C1x - C2x)) + ((C1y - C2y) * (C1y - C2y)) <=
//         ((C1r + C2r) * (C1r + C2r))) {
//         sfCircleShape_setFillColor(c1, sfWhite);
//         sfCircleShape_setFillColor(c2, sfWhite);
//         return 1;
//     }
//     return 0;
// }

static void analyse_events(sfRenderWindow *win, sfEvent *event, window_t *w)
{
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyQ))
        sfRenderWindow_close(win);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
        w->state_s = !w->state_s;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyL)
        w->state_l = !w->state_l;
}

void display_boundaries(sfRenderWindow *win, window_t *w)
{
    for (int i = 0; w->all_to[i]; i++) {
        sfRenderWindow_drawCircleShape(win, w->all_to[i]->area, NULL);
        // for (int j = 0; all_to[j]; j++) {
        //     // is_intersecting_circles(circles[i], circles[j]);
        // }
    }
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++)
            sfRenderWindow_drawRectangleShape(win, w->corners[i]->ac[j]->hitbox, NULL);
    }
}

void display_sprites(sfRenderWindow *win, window_t *w)
{
    for (int i = 0; w->all_to[i]; i++) {
        sfRenderWindow_drawSprite(win, w->all_to[i]->sprite, NULL);
        // for (int j = 0; all_to[j]; j++) {
        //     // is_intersecting_circles(circles[i], circles[j]);
        // }
    }
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++)
            sfRenderWindow_drawSprite(win, w->corners[i]->ac[j]->sprite, NULL);
    }
}

void handle_map_boundaries(aircraft_t *ac)
{
    sfVector2f pos = sfRectangleShape_getPosition(ac->hitbox);

    if (pos.x >= 1920)
        pos.x = 0;
    if (pos.y >= 1080)
        pos.y = 0;
    if (pos.x < 0)
        pos.x = 1919;
    if (pos.y < 0)
        pos.y += 1079;
    sfRectangleShape_setPosition(ac->hitbox, pos);
    sfSprite_setPosition(ac->sprite, pos);
    ac->pos = pos;
}

void ac_movement(window_t *w)
{
    sfVector2f vector_speed = {0, 0};

    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++) {
            handle_map_boundaries(w->corners[i]->ac[j]);
            // w->corners[i]->ac[j]->vector.x;
            vector_speed = (sfVector2f){((int)w->corners[i]->ac[j]->vector.x %
                5) - 2, ((int)w->corners[i]->ac[j]->vector.y % 5) - 2};
            sfRectangleShape_move(w->corners[i]->ac[j]->hitbox,
                vector_speed);// w->corners[i]->ac[j]->speed);
            sfSprite_move(w->corners[i]->ac[j]->sprite,
                vector_speed);// w->corners[i]->ac[j]->speed);
        }
    }
}

void while_window_open(sfRenderWindow *win, sfEvent event, window_t *w, sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float seconds = time.microseconds / 10000.0;

    while (sfRenderWindow_pollEvent(win, &event))
        analyse_events(win, &event, w);
    if (seconds/* > 1.0*/) {
        ac_movement(w);
        if (w->state_l == sfTrue)
            display_boundaries(win, w);
        if (w->state_s == sfTrue)
            display_sprites(win, w);
        print_framerate();
        sfClock_restart(clock);
    }
    sfRenderWindow_display(win);
}

int open_window(char **array)
{
    sfEvent event = {0};
    sfClock *clock = sfClock_create();
    // DONT DOUBLE LOOP FOR TOWERS
    window_t *w = init_window(array);

    free_array(array);
    sfRenderWindow_setFramerateLimit(w->win, 60);
    while (sfRenderWindow_isOpen(w->win)) {
        sfRenderWindow_clear(w->win, sfBlack);
        sfRenderWindow_drawSprite(w->win, w->bg, NULL);
        while_window_open(w->win, event, w, clock);
        for (int i = 0; w->corners[i]; i++)
            w->corners[i]->nb_ac = 0;
        w->corners = parse_in_corners(w->all_ac, w->nb_ac, w->corners);
    }
    sfClock_destroy(clock);
    my_destroy(w);
    return 0;
}
