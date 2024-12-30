/*
** EPITECH PROJECT, 2024
** bs_my_paint
** File description:
** init_button
*/

#include "window.h"
#include "math.h"

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
    sfRectangleShape_setOutlineColor(hitbox, sfGreen);
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
    // float dot_product = (ac->pos.x * ac->a_pos.x) + (ac->pos.y * ac->a_pos.y);
    // float norm_u = sqrt((ac->pos.x * ac->pos.x) + (ac->pos.y * ac->pos.y));
    // float norm_v = sqrt((ac->a_pos.x * ac->a_pos.x) + (ac->a_pos.y * ac->a_pos.y));
    // float cos_th = dot_product / (norm_u * norm_v);
    // if (cos_th < -1.0f) cos_th = -1.0f;
    // if (cos_th > 1.0f) cos_th = 1.0f;
    // float angle = acosf(cos_th) * (180.0f / 3.1416f);
    //
    // // Calculate the direction vector
    // float dx = ac->a_pos.x - ac->pos.x;
    // float dy = ac->a_pos.y - ac->pos.y;
    // // Calculate the angle in radians using atan2, then convert to degrees
    // float angle = atan2f(dy, dx) * (180.0f / 3.1416f);
    // // Apply the rotation
    // sfRectangleShape_setRotation(ac->hitbox, angle);
    // sfSprite_setRotation(ac->sprite, angle);
    // sfRectangleShape_rotate(ac->hitbox, angle);
    // sfSprite_rotate(ac->sprite, angle);
    return ac;
}

window_t *init_ac_to_tab(sfTexture *ac_texture, sfTexture *to_texture,
    window_t *w, char **infos)
{
    sfVector2i nb_ac_to = get_nb_ac_to(infos);
    int i = 0;
    int k = 0;
    char **array = NULL;

    w->all_ac = malloc(sizeof(aircraft_t *) * (nb_ac_to.x + 1));
    w->all_to = malloc(sizeof(tower_t *) * (nb_ac_to.y + 1));
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
    return w;
}

corner_t **parse_in_corners(aircraft_t **ac, int nb_ac, corner_t **corners)
{
    for (int i = 0; i < nb_ac; i++) {
        if (ac[i]->pos.x <= 960 && ac[i]->pos.y <= 540) {
            corners[0]->ac[corners[0]->nb_ac] = ac[i];
            corners[0]->nb_ac++;
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y < 540) {
            corners[1]->ac[corners[1]->nb_ac] = ac[i];
            corners[1]->nb_ac++;
        }
        if (ac[i]->pos.x <= 960 && ac[i]->pos.y > 540) {
            corners[2]->ac[corners[2]->nb_ac] = ac[i];
            corners[2]->nb_ac++;
        }
        if (ac[i]->pos.x > 960 && ac[i]->pos.y >= 540) {
            corners[3]->ac[corners[3]->nb_ac] = ac[i];
            corners[3]->nb_ac++;
        }
    }
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

window_t *init_window(char **array)
{
    window_t *w = malloc(sizeof(window_t));
    sfTexture *t_texture = sfTexture_createFromFile("assets/phare.png", NULL);
    sfTexture *ac_texture = sfTexture_createFromFile("assets/boat.png", NULL);
    sfTexture *bg_texture = sfTexture_createFromFile("assets/bg.jpg", NULL);

    w->win = sfRenderWindow_create((sfVideoMode){1920, 1080, 32}, "My_Radar",
        sfDefaultStyle, NULL);
    w->bg = sfSprite_create();
    sfSprite_setTexture(w->bg, bg_texture, sfTrue);
    w = init_ac_to_tab(ac_texture, t_texture, w, array);
    w->nb_ac = get_nb_ac_to(array).x;
    w->corners = init_corners(w->all_ac, w->nb_ac);
    w->state_l = sfTrue;
    w->state_s = sfTrue;
    return w;
}
