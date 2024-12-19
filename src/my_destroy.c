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

void my_destroy(sfRenderWindow *window, sfCircleShape **circles)
{
    for (int i = 0; circles[i]; i++)
        sfCircleShape_destroy(circles[i]);
    free(circles);
    sfRenderWindow_destroy(window);
}
