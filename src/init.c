/*
** EPITECH PROJECT, 2024
** bs_my_paint
** File description:
** init_button
*/

#include "window.h"

sfRectangleShape *init_hitbox(sfVector2f position)
{
    sfRectangleShape *hitbox = sfRectangleShape_create();

    sfRectangleShape_setPosition(hitbox, position);
    sfRectangleShape_setSize(hitbox, (sfVector2f){20, 20});
    // sfRectangleShape_setOutlineColor(hitbox, sfGreen);
    sfRectangleShape_setOutlineThickness(hitbox, 1);
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    return hitbox;
}

sfSprite *init_sprite(sfTexture *texture, sfVector2f pos)
{
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, (sfVector2f){0.07, 0.07});
    return sprite;
}

aircraft_t *init_aircraft(char **array, sfTexture *texture)
{
    aircraft_t *ac = malloc(sizeof(aircraft_t));

    ac->pos = (sfVector2f){my_getnbr(array[1]), my_getnbr(array[2])};
    ac->a_pos = (sfVector2f){my_getnbr(array[3]), my_getnbr(array[4])};
    ac->hitbox = init_hitbox(ac->pos);
    ac->vector = (sfVector2f){ac->a_pos.x - ac->pos.x,
        ac->a_pos.y - ac->pos.y};
    ac->speed = my_getnbr(array[5]);
    ac->delay = my_getnbr(array[6]);
    ac->sprite = init_sprite(texture, ac->pos);
    return ac;
}

aircraft_t **init_aircrafts_tab(sfTexture *texture, char **infos)
{
    int nb_ac = get_nb_ac(infos);
    aircraft_t **aircrafts = malloc(sizeof(aircraft_t *) * (nb_ac + 1));
    int i = 0;
    char **array = NULL;

    for (int j = 0; infos[j]; j++) {
        if (infos[j][0] == 'A') {
            array = my_str_to_word_array(infos[j], "\t ");
            aircrafts[i] = init_aircraft(array, texture);
            // free_array(array);
            i++;
        }
    }
    aircrafts[i] = NULL;
    return aircrafts;
}

corner_t **parse_in_corners(aircraft_t **ac, int nb_ac, corner_t **corners)
{
    for (int i = 0; i < nb_ac; i++) {
        if (ac[i]->pos.x < 960 && ac[i]->pos.y < 540) {
            corners[0]->ac[corners[0]->nb_ac++] = ac[i];
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfRed);
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y < 540) {
            corners[1]->ac[corners[1]->nb_ac++] = ac[i];
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfGreen);
        }
        if (ac[i]->pos.x < 960 && ac[i]->pos.y > 540) {
            corners[2]->ac[corners[2]->nb_ac++] = ac[i];
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfBlue);
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y > 540) {
            corners[3]->ac[corners[3]->nb_ac++] = ac[i];
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfYellow);
        }
    }
    for (int j = 0; j < 4; j++)
        corners[j]->ac[corners[j]->nb_ac] = NULL;
    return corners;
}

corner_t **init_corners(aircraft_t **ac, int nb_ac)
{
    corner_t **corners = malloc(sizeof(corner_t *) * 5);

    for (int i = 0; i < 4; i++) {
        corners[i] =  malloc(sizeof(corner_t));
        corners[i]->ac = malloc(sizeof(aircraft_t *) * nb_ac);
        corners[i]->nb_ac = 0;
    }
    corners = parse_in_corners(ac, nb_ac, corners);
    corners[4] = NULL;
    return corners;
}

// sfCircleShape *init_circle(sfVector2f position, float radius)
// {
//     sfCircleShape *circle = sfCircleShape_create();
//     sfCircleShape_setPosition(circle, position);
//     sfCircleShape_setRadius(circle, radius);
//     sfCircleShape_setOutlineColor(circle, sfWhite);
//     sfCircleShape_setOutlineThickness(circle, 1);
//     sfCircleShape_setFillColor(circle, sfTransparent);
//     return circle;
// }

// sfCircleShape **init_circles(int nbr_circle, sfVector2f position)
// {
//     sfCircleShape **circles = malloc(sizeof(sfCircleShape *) * nbr_circle + 1);

//     for (int i = 0; i < nbr_circle; i++)
//         circles[i] = init_circle(position, rand() % 20);
//     circles[nbr_circle] = NULL;
//     return circles;
// }
