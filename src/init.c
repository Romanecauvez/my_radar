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
    sfRectangleShape_setOutlineColor(hitbox, sfGreen);
    sfRectangleShape_setOutlineThickness(hitbox, 1);
    sfRectangleShape_setFillColor(hitbox, sfTransparent);
    return hitbox;
}

static sfSprite *init_sprite(sfTexture *texture, sfVector2f pos,
    sfVector2f scale, sfVector2f origin)
{
    sfSprite *sprite = sfSprite_create();

    sfSprite_setOrigin(sprite, origin);
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return sprite;
}

tower_t *init_tower(char **array, sfTexture *texture)
{
    tower_t *t = malloc(sizeof(tower_t));

    t->pos = (sfVector2f){my_getnbr(array[1]), my_getnbr(array[2])};
    t->area = init_circle(t->pos, my_getnbr(array[3]));
    t->sprite = init_sprite(texture, t->pos, (sfVector2f){0.1, 0.1},
        (sfVector2f){250, 250});
    return t;
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
    ac->sprite = init_sprite(texture, ac->pos, (sfVector2f){0.07, 0.07},
        (sfVector2f){0, 0});
    sfSprite_setRotation(ac->sprite,
        atan2(ac->vector.y, ac->vector.x) * 180 / 3.14);
    sfRectangleShape_setRotation(ac->hitbox,
        atan2(ac->vector.y, ac->vector.x) * 180 / 3.14);
    return ac;
}

static window_t *init_ac_to_tab(sfTexture *ac_texture, sfTexture *to_texture,
    window_t *w, char **infos)
{
    sfVector2i nb_ac_to = get_nb_ac_to(infos);

    w->all_ac = malloc(sizeof(aircraft_t *) * (nb_ac_to.x + 1));
    w->all_to = malloc(sizeof(tower_t *) * (nb_ac_to.y + 1));
    parse_ac_to_infos(infos, w, ac_texture, to_texture);
    return w;
}

static corner_t **init_corners(int nb_ac)
{
    corner_t **corners = malloc((sizeof(corner_t *) * 4) + sizeof(NULL));

    for (int i = 0; i < 4; i++) {
        corners[i] = malloc(sizeof(corner_t));
        corners[i]->ac = malloc(sizeof(aircraft_t *) * nb_ac + sizeof(NULL));
        corners[i]->nb_ac = 0;
    }
    corners[4] = NULL;
    return corners;
}

sfText *init_text(sfVector2f position, int size)
{
    sfText *text = sfText_create();

    sfText_setPosition(text, position);
    sfText_setFont(text, sfFont_createFromFile("assets/Milanello.otf"));
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfBlack);
    return text;
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
    w->corners = init_corners(w->nb_ac);
    w->state_l = sfTrue;
    w->state_s = sfTrue;
    w->fps = init_text((sfVector2f){1480, 0}, 40);
    w->seconds = init_text((sfVector2f){1650, 0}, 40);
    return w;
}
