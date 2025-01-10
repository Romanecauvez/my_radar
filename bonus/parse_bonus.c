/*
** EPITECH PROJECT, 2025
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** parsing
*/

#include "window.h"

void parse_ac_to_infos(char **infos, window_t *w, sfTexture *ac_texture,
    sfTexture *to_texture)
{
    char **array = NULL;
    int i = 0;
    int k = 0;

    for (int j = 0; infos[j]; j++) {
        array = my_str_to_word_array(infos[j], "\t ");
        if (infos[j][0] == 'A') {
            w->all_ac[i] = init_aircraft(array, ac_texture);
            i++;
        }
        if (infos[j][0] == 'T') {
            w->all_to[k] = init_tower(array, to_texture);
            k++;
        }
        free_array(array);
    }
    w->all_ac[i] = NULL;
    w->all_to[k] = NULL;
}

static void parse_top_corners(aircraft_t *ac, corner_t **corners)
{
    if (ac->pos.x <= 960 && ac->pos.y <= 540) {
        sfRectangleShape_setOutlineColor(ac->hitbox, sfRed);
        corners[0]->ac[corners[0]->nb_ac] = ac;
        corners[0]->nb_ac++;
    }
    if (ac->pos.x > 960 && ac->pos.y < 540) {
        sfRectangleShape_setOutlineColor(ac->hitbox, sfGreen);
        corners[1]->ac[corners[1]->nb_ac] = ac;
        corners[1]->nb_ac++;
    }
}

static void parse_bot_corners(aircraft_t *ac, corner_t **corners)
{
    if (ac->pos.x <= 960 && ac->pos.y > 540) {
        sfRectangleShape_setOutlineColor(ac->hitbox, sfBlue);
        corners[2]->ac[corners[2]->nb_ac] = ac;
        corners[2]->nb_ac++;
    }
    if (ac->pos.x > 960 && ac->pos.y >= 540) {
        sfRectangleShape_setOutlineColor(ac->hitbox, sfYellow);
        corners[3]->ac[corners[3]->nb_ac] = ac;
        corners[3]->nb_ac++;
    }
}

corner_t **parse_in_corners(window_t *w, int second)
{
    for (unsigned int i = 0; i < w->nb_ac; i++) {
        if (second < (int)w->all_ac[i]->delay)
            continue;
        parse_top_corners(w->all_ac[i], w->corners);
        parse_bot_corners(w->all_ac[i], w->corners);
    }
    for (int j = 0; j < 4; j++)
        w->corners[j]->ac[w->corners[j]->nb_ac] = NULL;
    return w->corners;
}
