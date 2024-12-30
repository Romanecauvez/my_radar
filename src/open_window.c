/*
** EPITECH PROJECT, 2023
** open_window.c
** File description:
** open a window
*/

#include "window.h"
#include <math.h>

int is_in_area(sfVector2f vector1, tower_t *tower)
{
    sfVector2f vector2 = tower->pos;
    float area_r = sfCircleShape_getRadius(tower->area);
    float boatx = vector1.x + 20;
    float boaty = vector1.y + 20;
    float areax = vector2.x + area_r;
    float areay = vector2.y + area_r;

    if (((boatx - areax) * (boatx - areax)) + ((boaty - areay) * (boaty - areay)) <=
        ((20 + area_r) * (20 + area_r))) {
        return 1;
    }
    return 0;
}

static void analyse_events(sfRenderWindow *win, sfEvent *event, window_t *w)
{
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyQ))
        sfRenderWindow_close(win);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
        w->state_s = !w->state_s;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyL)
        w->state_l = !w->state_l;
}

void display_boundaries(sfRenderWindow *win, window_t *w)
{
    for (int i = 0; w->all_to[i]; i++) {
        sfRenderWindow_drawCircleShape(win, w->all_to[i]->area, NULL);
    }
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++)
            sfRenderWindow_drawRectangleShape(win, w->corners[i]->ac[j]->hitbox, NULL);
    }
}

int ac_cmp(aircraft_t *ac1, aircraft_t *ac2)
{
    if (ac1->a_pos.x == ac2->a_pos.x && ac1->a_pos.y == ac2->a_pos.y &&
        ac1->delay == ac2->delay && ac1->pos.x == ac2->pos.x &&
        ac1->pos.y == ac2->pos.y && ac1->speed == ac2->speed)
        return 1;
    return 0;
}

void remove_aircraft(aircraft_t *ac, window_t *w)
{
    aircraft_t *last_ac = w->all_ac[w->nb_ac - 1];

    for (int i = 0; w->all_ac[i]; i++) {
        if (w->all_ac[i] == ac) {
            w->all_ac[i] = last_ac;
            w->nb_ac--;
            w->all_ac[w->nb_ac] = NULL;
        }
    }
    // sfRectangleShape_destroy(ac->hitbox);
    // sfSprite_destroy(ac->sprite);
}

void is_intersecting_ac(window_t *w, int j, int i)
{
    sfVector2f pos1 = {0, 0};
    sfVector2f pos2 = {0, 0};

    for (int x = j + 1; w->corners[i]->ac[x]; x++) {
        pos1 = sfRectangleShape_getPosition(w->corners[i]->ac[j]->hitbox);
        pos2 = sfRectangleShape_getPosition(w->corners[i]->ac[x]->hitbox);
        // for (int i = 0; w->all_to[i]; i++) {
        //     if (is_in_area(pos1, w->all_to[i]) || is_in_area(pos2, w->all_to[i]))
        //         return;
        // }
        if ((pos2.x + 10 >= pos1.x - 10 && pos2.x - 10 <= pos1.x + 10)
            &&
            (pos2.y + 10 >= pos1.y - 10 && pos2.y - 10 <= pos1.y + 10)) {
            remove_aircraft(w->corners[i]->ac[j], w);
            remove_aircraft(w->corners[i]->ac[x], w);
        }
    }
}

void is_arrived(window_t *w, aircraft_t *ac)
{
    if (ac->pos.x == ac->a_pos.x && ac->pos.y == ac->a_pos.y)
        remove_aircraft(ac, w);
}

void display_sprites(sfRenderWindow *win, window_t *w)
{
    for (int i = 0; w->all_to[i]; i++)
        sfRenderWindow_drawSprite(win, w->all_to[i]->sprite, NULL);
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++) {
            sfRenderWindow_drawSprite(win, w->corners[i]->ac[j]->sprite, NULL);
            is_intersecting_ac(w, j, i);
            is_arrived(w, w->corners[i]->ac[j]);
        }
    }
}

void handle_map_boundaries(aircraft_t *ac)
{
    sfVector2f pos = sfRectangleShape_getPosition(ac->hitbox);

    if (pos.x >= 1920)
        pos.x = 0;
    if (pos.y >= 1080)
        pos.y = 0;
    if (pos.x < 0)
        pos.x = 1919;
    if (pos.y < 0)
        pos.y += 1079;
    sfRectangleShape_setPosition(ac->hitbox, pos);
    sfSprite_setPosition(ac->sprite, pos);
    ac->pos = pos;
}

void ac_movement(window_t *w)
{
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++) {
            handle_map_boundaries(w->corners[i]->ac[j]);
            sfVector2f v = w->corners[i]->ac[j]->vector;
            float magnitude = sqrtf(v.x * v.x + v.y * v.y);
            // Normalize the v vector
            sfVector2f normalized_v = {v.x / magnitude, v.y / magnitude};
            // Scale the normalized vector by the speed
            sfVector2f move_vector = {normalized_v.x *
                (w->corners[i]->ac[j]->speed / 60), normalized_v.y *
                (w->corners[i]->ac[j]->speed / 60)};
            // vector_speed = (sfVector2f){w->corners[i]->ac[j]->speed / 60, w->corners[i]->ac[j]->speed / 60};
            sfRectangleShape_move(w->corners[i]->ac[j]->hitbox,
                move_vector);// w->corners[i]->ac[j]->speed);
            sfSprite_move(w->corners[i]->ac[j]->sprite,
                move_vector);// w->corners[i]->ac[j]->speed);
        }
    }
}

sfText *init_text(sfVector2f position, char *text_str,
    int size)
{
    sfText *text = sfText_create();

    sfText_setPosition(text, position);
    sfText_setString(text, text_str);
    sfText_setFont(text, sfFont_createFromFile("assets/Milanello.otf"));
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfBlack);
    return text;
}

static char *score_convert(int nbr)
{
    int nb_len = 0;
    char *str = NULL;
    int i = 0;

    for (int tmp = nbr; tmp; nb_len++)
        tmp /= 10;
    str = malloc(sizeof(char) * nb_len + 1);
    if (!str)
        return NULL;
    i = nb_len - 1;
    for (; i >= 0; i--) {
        str[i] = nbr % 10 + 48;
        nbr /= 10;
    }
    str[nb_len] = '\0';
    return str;
}

void while_window_open(sfEvent event, window_t *w, sfClock *clock)
{
    static int first = 1;
    static int fps = 0;
    static int second = 0;
    sfTime elapsed = {0};
    static char *fps_str = "60";
    static char *second_str = "0";
    sfText *fps_seconds = NULL;

    while (sfRenderWindow_pollEvent(w->win, &event))
        analyse_events(w->win, &event, w);
    if (first == 1) {
        clock = sfClock_create();
        first = 0;
    }
    elapsed = sfClock_getElapsedTime(clock);
    if (w->state_l == sfTrue)
        display_boundaries(w->win, w);
    if (w->state_s == sfTrue)
        display_sprites(w->win, w);
    ac_movement(w);
    if (sfTime_asSeconds(elapsed) >= 1) {
        second++;
        fps_str = score_convert(fps);
        second_str = score_convert(second);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
    fps_seconds = init_text((sfVector2f){750,0}, fps_str, 40);
    sfRenderWindow_drawText(w->win, fps_seconds, NULL);
    sfText_destroy(fps_seconds);
    fps_seconds = init_text((sfVector2f){920,0}, second_str, 40);
    sfRenderWindow_drawText(w->win, fps_seconds, NULL);
    sfText_destroy(fps_seconds);
    sfRenderWindow_display(w->win);
}

int open_window(char **array)
{
    sfEvent event = {0};
    sfClock *clock = sfClock_create();
    window_t *w = init_window(array);
    sfText *text = init_text((sfVector2f){820, 0}, "FPS,\t\tSecond(s)", 40);

    free_array(array);
    sfRenderWindow_setFramerateLimit(w->win, 60);
    while (sfRenderWindow_isOpen(w->win)) {
        sfRenderWindow_clear(w->win, sfBlack);
        sfRenderWindow_drawSprite(w->win, w->bg, NULL);
        sfRenderWindow_drawText(w->win, text, NULL);
        while_window_open(event, w, clock);
        for (int i = 0; w->corners[i]; i++)
            w->corners[i]->nb_ac = 0;
        w->corners = parse_in_corners(w->all_ac, w->nb_ac, w->corners);
    }
    sfClock_destroy(clock);
    my_destroy(w);
    return 0;
}
