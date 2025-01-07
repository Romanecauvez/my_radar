/*
** EPITECH PROJECT, 2025
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** cmp
*/

#include "window.h"

int ac_cmp(aircraft_t *ac1, aircraft_t *ac2)
{
    if (ac1->a_pos.x == ac2->a_pos.x && ac1->a_pos.y == ac2->a_pos.y &&
        ac1->delay == ac2->delay && ac1->pos.x == ac2->pos.x &&
        ac1->pos.y == ac2->pos.y && ac1->speed == ac2->speed)
        return 1;
    return 0;
}
