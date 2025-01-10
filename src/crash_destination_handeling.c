/*
** EPITECH PROJECT, 2025
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** crash_destination_handeling
*/

#include "window.h"

static void remove_aircraft(aircraft_t *ac, window_t *w)
{
    aircraft_t *last_ac = NULL;

    if (w->nb_ac == 0)
        return;
    last_ac = w->all_ac[w->nb_ac - 1];
    for (int i = 0; w->all_ac[i]; i++) {
        if (w->all_ac[i] == ac) {
            w->all_ac[i] = last_ac;
            w->nb_ac--;
            w->all_ac[w->nb_ac] = NULL;
        }
    }
}

void is_arrived(window_t *w, aircraft_t *ac)
{
    if ((ac->a_pos.x >= ac->pos.x + ac->speed &&
        ac->a_pos.x <= ac->pos.x - ac->speed) &&
        (ac->a_pos.y >= ac->pos.y + ac->speed &&
        ac->a_pos.y <= ac->pos.y - ac->speed)) {
        remove_aircraft(ac, w);
    }
}

static int is_in_area(sfVector2f pos_ac, tower_t *tower)
{
    sfVector2f pos_to = tower->pos;
    float area_r = sfCircleShape_getRadius(tower->area);

    if (((pos_ac.x - pos_to.x) * (pos_ac.x - pos_to.x)) +
        ((pos_ac.y - pos_to.y) * (pos_ac.y - pos_to.y)) <=
        ((20 + area_r) * (20 + area_r))) {
        return 1;
    }
    return 0;
}

static int is_in_any_area(tower_t **all_to, sfVector2f pos1, sfVector2f pos2)
{
    for (int i = 0; all_to[i]; i++) {
        if (is_in_area(pos1, all_to[i]) == 1 &&
            is_in_area(pos2, all_to[i]) == 1)
            return 1;
    }
    return 0;
}

void is_intersecting_ac(window_t *w, int j, int i)
{
    sfVector2f pos1 = {0, 0};
    sfVector2f pos2 = {0, 0};

    for (int x = j + 1; w->corners[i]->ac[x]; x++) {
        pos1 = w->corners[i]->ac[j]->pos;
        pos2 = w->corners[i]->ac[x]->pos;
        if (is_in_any_area(w->all_to, pos1, pos2) == 1)
            return;
        if ((pos2.x + 10 >= pos1.x - 10 && pos2.x - 10 <= pos1.x + 10) &&
            (pos2.y + 10 >= pos1.y - 10 && pos2.y - 10 <= pos1.y + 10)) {
            remove_aircraft(w->corners[i]->ac[j], w);
            remove_aircraft(w->corners[i]->ac[x], w);
        }
    }
}
