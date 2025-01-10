/*
** EPITECH PROJECT, 2025
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** displays
*/

#include "window.h"

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
