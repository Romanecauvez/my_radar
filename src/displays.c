/*
** EPITECH PROJECT, 2025
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** displays
*/

#include "window.h"

int display_window(window_t *w, sfText *text, int second, sfClock *clock)
{
    sfRenderWindow_clear(w->win, sfBlack);
    sfRenderWindow_drawSprite(w->win, w->bg, NULL);
    sfRenderWindow_drawText(w->win, text, NULL);
    for (int i = 0; w->corners[i]; i++)
        w->corners[i]->nb_ac = 0;
    w->corners = parse_in_corners(w, second);
    second = while_window_open(w, clock);
    return second;
}

void display_text(window_t *w, char *fps_str, char *second_str)
{
    sfText_setString(w->fps, fps_str);
    sfRenderWindow_drawText(w->win, w->fps, NULL);
    sfText_setString(w->seconds, second_str);
    sfRenderWindow_drawText(w->win, w->seconds, NULL);
}

void display_boundaries(window_t *w)
{
    for (int i = 0; w->all_to[i]; i++)
        sfRenderWindow_drawCircleShape(w->win, w->all_to[i]->area, NULL);
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++)
            sfRenderWindow_drawRectangleShape(w->win,
                w->corners[i]->ac[j]->hitbox, NULL);
    }
}

void display_sprites(window_t *w)
{
    for (int i = 0; w->all_to[i]; i++)
        sfRenderWindow_drawSprite(w->win, w->all_to[i]->sprite, NULL);
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++)
            sfRenderWindow_drawSprite(w->win,
                w->corners[i]->ac[j]->sprite, NULL);
    }
}
