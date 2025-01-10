/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** my_destroy.c
*/

#include "window.h"

int free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
    return 0;
}

static void my_destroy_textures(window_t *w)
{
    sfTexture_destroy((sfTexture *)sfSprite_getTexture(w->bg));
    if ((!w->all_ac || !w->all_ac[0] || !w->all_ac[0]->sprite) &&
        (!w->all_to || !w->all_to[0] || !w->all_to[0]->sprite))
        return;
    if (w->all_ac[0] && w->all_ac[0]->sprite)
        sfTexture_destroy((sfTexture *)
            sfSprite_getTexture(w->all_ac[0]->sprite));
    if (w->all_to[0] && w->all_to[0]->sprite)
        sfTexture_destroy((sfTexture *)
            sfSprite_getTexture(w->all_to[0]->sprite));
}

static void my_destroy_aircrafts(window_t *w)
{
    if (!w->all_ac)
        return;
    for (int i = 0; w->all_ac[i]; i++) {
        sfRectangleShape_destroy(w->all_ac[i]->hitbox);
        sfSprite_destroy(w->all_ac[i]->sprite);
        free(w->all_ac[i]);
    }
    free(w->all_ac);
}

static void my_destroy_towers(window_t *w)
{
    if (!w->all_to)
        return;
    for (int i = 0; w->all_to[i]; i++) {
        sfCircleShape_destroy(w->all_to[i]->area);
        sfSprite_destroy(w->all_to[i]->sprite);
    }
    free(w->all_to);
}

int my_destroy(window_t *w)
{
    my_destroy_textures(w);
    sfSprite_destroy(w->bg);
    my_destroy_aircrafts(w);
    my_destroy_towers(w);
    for (int i = 0; i < 4; i++)
        free(w->corners[i]->ac);
    free(w->corners);
    sfRenderWindow_destroy(w->win);
    return 0;
}
