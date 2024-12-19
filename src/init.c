/*
** EPITECH PROJECT, 2024
** bs_my_paint
** File description:
** init_button
*/

#include "window.h"

static sfCircleShape *init_circle(sfVector2f position, float radius)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setOrigin(circle, (sfVector2f){radius, radius});
    sfCircleShape_setPosition(circle, position);
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setOutlineThickness(circle, 2);
    sfCircleShape_setFillColor(circle, sfTransparent);
    return circle;
}

static sfRectangleShape *init_hitbox(sfVector2f position)
{
    sfRectangleShape *hitbox = sfRectangleShape_create();

    sfRectangleShape_setPosition(hitbox, position);
    sfRectangleShape_setSize(hitbox, (sfVector2f){20, 20});
    // sfRectangleShape_setOutlineColor(hitbox, sfGreen);
    sfRectangleShape_setOutlineThickness(hitbox, 1);
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    return hitbox;
}

sfSprite *init_sprite(sfTexture *texture, sfVector2f pos, sfVector2f scale,
    sfVector2f origin)
{
    sfSprite *sprite = sfSprite_create();

    sfSprite_setOrigin(sprite, origin);
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return sprite;
}

static tower_t *init_tower(char **array, sfTexture *texture)
{
    tower_t *t = malloc(sizeof(tower_t));

    t->pos = (sfVector2f){my_getnbr(array[1]), my_getnbr(array[2])};
    t->area = init_circle(t->pos, my_getnbr(array[3]));
    t->sprite = init_sprite(texture, t->pos, (sfVector2f){0.1, 0.1},
        (sfVector2f){250, 250});
    return t;
}

tower_t **init_towers_tab(sfTexture *texture, char **infos)
{
    int nb_t = get_nb_to(infos);
    tower_t **towers = malloc(sizeof(tower_t *) * (nb_t + 1));
    int i = 0;
    char **array = NULL;

    for (int j = 0; infos[j]; j++) {
        if (infos[j][0] == 'T') {
            array = my_str_to_word_array(infos[j], "\t ");
            towers[i] = init_tower(array, texture);
            free_array(array);
            i++;
        }
    }
    towers[i] = NULL;
    return towers;
}

static aircraft_t *init_aircraft(char **array, sfTexture *texture)
{
    aircraft_t *ac = malloc(sizeof(aircraft_t));

    ac->pos = (sfVector2f){my_getnbr(array[1]), my_getnbr(array[2])};
    ac->a_pos = (sfVector2f){my_getnbr(array[3]), my_getnbr(array[4])};
    ac->hitbox = init_hitbox(ac->pos);
    ac->vector = (sfVector2f){ac->a_pos.x - ac->pos.x,
        ac->a_pos.y - ac->pos.y};
    ac->speed = my_getnbr(array[5]);
    ac->delay = my_getnbr(array[6]);
    ac->sprite = init_sprite(texture, ac->pos, (sfVector2f){0.07, 0.07},
        (sfVector2f){0, 0});
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
            free_array(array);
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
            corners[0]->ac[corners[0]->nb_ac] = ac[i];
            corners[0]->nb_ac++;
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfRed);
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y < 540) {
            corners[1]->ac[corners[1]->nb_ac] = ac[i];
            corners[1]->nb_ac++;
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfGreen);
        }
        if (ac[i]->pos.x < 960 && ac[i]->pos.y > 540) {
            corners[2]->ac[corners[2]->nb_ac] = ac[i];
            corners[2]->nb_ac++;
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfBlue);
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y > 540) {
            corners[3]->ac[corners[3]->nb_ac] = ac[i];
            corners[3]->nb_ac++;
            sfRectangleShape_setOutlineColor(ac[i]->hitbox, sfYellow);
        }
    }
    // printf("CT:%d\t", corners[0]->nb_ac + corners[1]->nb_ac + corners[2]->nb_ac + corners[3]->nb_ac);
    for (int j = 0; j < 4; j++)
        corners[j]->ac[corners[j]->nb_ac] = NULL;
    return corners;
}

corner_t **init_corners(aircraft_t **ac, int nb_ac)
{
    corner_t **corners = malloc((sizeof(corner_t *) * 4) + sizeof(NULL));

    for (int i = 0; i < 4; i++) {
        corners[i] = malloc(sizeof(corner_t));
        corners[i]->ac = malloc(sizeof(aircraft_t *) * nb_ac + sizeof(NULL));
        corners[i]->nb_ac = 0;
    }
    corners = parse_in_corners(ac, nb_ac, corners);
    corners[4] = NULL;
    return corners;
}

window_t *init_window(char **array, aircraft_t **all_ac)
{
    window_t *w = malloc(sizeof(window_t));
    sfTexture *t_texture = sfTexture_createFromFile("assets/phare.png", NULL);

    w->all_to = init_towers_tab(t_texture, array);
    w->nb_ac = get_nb_ac(array);
    w->corners = init_corners(all_ac, w->nb_ac);
    w->state_l = sfTrue;
    w->state_s = sfTrue;
    return w;
}

// sfCircleShape **init_circles(int nbr_circle, sfVector2f position)
// {
//     sfCircleShape **circles = malloc(sizeof(sfCircleShape *) *
//         nbr_circle + 1);

//     for (int i = 0; i < nbr_circle; i++)
//         circles[i] = init_circle(position, rand() % 20);
//     circles[nbr_circle] = NULL;
//     return circles;
// }
