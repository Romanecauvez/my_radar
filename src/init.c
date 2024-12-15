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

aircraft_t *init_aircraft(sfVector2f pos, sfTexture *texture)
{
    aircraft_t *ac = malloc(sizeof(aircraft_t));

    ac->hitbox = init_hitbox(pos);
    ac->pos = pos;
    ac->vector = (sfVector2f){0, 5};
    ac->delay = 0;
    ac->speed = 10;
    ac->sprite = init_sprite(texture, pos);
    return ac;
}

aircraft_t **init_aircrafts_tab(sfTexture *texture, int nb_ac) // char **infos)
{
    aircraft_t **aircrafts = malloc(sizeof(aircraft_t *) * (nb_ac + 1));

    for (int i = 0; i < nb_ac; i++)
        aircrafts[i] = init_aircraft((sfVector2f){rand() % 1920, rand() % 1080}, texture);
    aircrafts[nb_ac] = NULL;
    return aircrafts;
}

    // aircrafts[0] = init_aircraft((sfVector2f){400, 400}, texture);
    // aircrafts[1] = init_aircraft((sfVector2f){800, 900}, texture);
    // aircrafts[2] = init_aircraft((sfVector2f){100, 1000}, texture);
    // aircrafts[3] = init_aircraft((sfVector2f){100, 90}, texture);
    // aircrafts[4] = init_aircraft((sfVector2f){900, 100}, texture);
    // aircrafts[5] = init_aircraft((sfVector2f){1600, 900}, texture);
    // aircrafts[6] = init_aircraft((sfVector2f){100, 100}, texture);
    // aircrafts[7] = init_aircraft((sfVector2f){100, 200}, texture);

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

    // for
    corners[0] =  malloc(sizeof(corner_t));
    corners[0]->ac = malloc(sizeof(aircraft_t *) * nb_ac);
    corners[0]->nb_ac = 0;
    corners[1] =  malloc(sizeof(corner_t));
    corners[1]->ac = malloc(sizeof(aircraft_t *) * nb_ac);
    corners[1]->nb_ac = 0;
    corners[2] =  malloc(sizeof(corner_t));
    corners[2]->ac = malloc(sizeof(aircraft_t *) * nb_ac);
    corners[2]->nb_ac = 0;
    corners[3] =  malloc(sizeof(corner_t));
    corners[3]->ac = malloc(sizeof(aircraft_t *) * nb_ac);
    corners[3]->nb_ac = 0;
    corners = parse_in_corners(ac, nb_ac, corners);
    corners[4] = NULL;
    return corners;
}

// sfCircleShape **init_circles(int nbr_circle, sfVector2f position)
// {
//     sfCircleShape **circles = malloc(sizeof(sfCircleShape *) * nbr_circle + 1);

//     for (int i = 0; i < nbr_circle; i++)
//         circles[i] = init_circle(position, rand() % 20);
//     circles[nbr_circle] = NULL;
//     return circles;
// }

sfCircleShape *init_circle(sfVector2f position, float radius)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfCircleShape_setPosition(circle, position);
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOutlineColor(circle, sfWhite);
    sfCircleShape_setOutlineThickness(circle, 1);
    sfCircleShape_setFillColor(circle, sfTransparent);
    return circle;
}
