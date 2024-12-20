/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** my_destroy.c
*/

#include <SFML/Graphics.h>
#include "window.h"

void free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void my_destroy(window_t *w)
{
    sfTexture *ac_texture = (sfTexture *)sfSprite_getTexture(w->all_ac[0]->sprite);
    sfTexture *to_texture = (sfTexture *)sfSprite_getTexture(w->all_to[0]->sprite);

    sfTexture_destroy((sfTexture *)sfSprite_getTexture(w->bg));
    sfSprite_destroy(w->bg);
    for (int i = 0; w->all_ac[i]; i++) {
        sfRectangleShape_destroy(w->all_ac[i]->hitbox);
        sfSprite_destroy(w->all_ac[i]->sprite);
        free(w->all_ac[i]);
    }
    free(w->all_ac);
    sfTexture_destroy(ac_texture);
    for (int i = 0; w->all_to[i]; i++) {
        sfCircleShape_destroy(w->all_to[i]->area);
        sfSprite_destroy(w->all_to[i]->sprite);
    }
    free(w->all_to);
    sfTexture_destroy(to_texture);
    for (int i = 0; i < 4; i++)
        free(w->corners[i]->ac);
    free(w->corners);
    sfRenderWindow_destroy(w->win);
}
