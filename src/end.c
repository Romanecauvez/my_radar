/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myhunter-romane.cauvez
** File description:
** end
*/

#include "window.h"

static char *score_convert(int nbr)
{
    char *str = malloc(sizeof(char) * 3);

    if (!str)
        return NULL;
    str[0] = nbr / 10 + 48;
    str[1] = nbr % 10 + 48;
    str[2] = '\0';
    return str;
}

static int print_score(int score, sfRenderWindow *win, sfSprite *my_sprite)
{
    char *score_nbr_str = score_convert(score);
    sfText *nb_score = init_text("assets/Sevillana-Regular.ttf",
        (sfVector2f){1860, 0}, score_nbr_str, 50);

    free(score_nbr_str);
    sfRenderWindow_drawText(win, nb_score, NULL);
    sfText_destroy(nb_score);
    if (sfSprite_getPosition(my_sprite).x >= 2086) {
        sfSprite_setPosition(my_sprite, (sfVector2f){-166, (rand() % 914)});
        if (score > 0)
            return -1;
    }
    return 0;
}

int end_of_function(int score, sfRenderWindow *win, sfSprite *my_sprite,
    sfText *score_str)
{
    score += print_score(score, win, my_sprite);
    sfRenderWindow_drawText(win, score_str, NULL);
    sfRenderWindow_display(win);
    return score;
}
