/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** get_nb_towers_ac
*/

#include "window.h"

sfVector2i get_nb_ac_to(char **array)
{
    int nb_ac = 0;
    int nb_to = 0;

    for (int i = 0; array[i]; i++) {
        if (array[i][0] == 'A')
            nb_ac++;
        if (array[i][0] == 'T')
            nb_to++;
    }
    return (sfVector2i){nb_ac, nb_to};
}
