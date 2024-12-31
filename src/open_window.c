/*
** EPITECH PROJECT, 2023
** open_window.c
** File description:
** open a window
*/

#include "window.h"
#include <math.h>

int is_in_area(sfVector2f pos_ac, tower_t *tower)
{
    sfVector2f pos_to = tower->pos;
    float area_r = sfCircleShape_getRadius(tower->area);

    if (((pos_ac.x - pos_to.x) * (pos_ac.x - pos_to.x)) +
        ((pos_ac.y - pos_to.y) * (pos_ac.y - pos_to.y)) <=
        ((area_r) * (area_r))) {
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
    aircraft_t *last_ac = NULL;

    if (w->nb_ac == 0)
        return;
    last_ac = w->all_ac[w->nb_ac - 1];
    for (int i = 0; w->all_ac[i]; i++) {
        if (w->all_ac[i] == ac) {
            w->all_ac[i] = last_ac;
            w->nb_ac--;
            w->all_ac[w->nb_ac] = NULL;
        }
    }
}

void is_intersecting_ac(window_t *w, int j, int i)
{
    sfVector2f pos1 = {0, 0};
    sfVector2f pos2 = {0, 0};

    for (int x = j + 1; w->corners[i]->ac[x]; x++) {
        pos1 = sfRectangleShape_getPosition(w->corners[i]->ac[j]->hitbox);
        pos2 = sfRectangleShape_getPosition(w->corners[i]->ac[x]->hitbox);
        for (int i = 0; w->all_to[i]; i++) {
            if (is_in_area(pos1, w->all_to[i]) == 1 && is_in_area(pos2, w->all_to[i]) == 1)
                return;
        }
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
    // if ((ac->a_pos.x >= old_pos.x && ac->a_pos.x <= ac->pos.x) && (ac->a_pos.y >= old_pos.y && ac->a_pos.y <= ac->pos.y)) {
    if ((int)ac->a_pos.x == (int)ac->pos.x && (int)ac->a_pos.y == (int)ac->pos.y) {
        // printf("x : %f, y : %f\n", ac->pos.x, ac->pos.y);
        // printf("a_x : %f, a_y : %f\n", ac->a_pos.x, ac->a_pos.y);
        remove_aircraft(ac, w);
    }
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
    sfVector2f v = {0, 0};
    float magnitude = 0.0;
    sfVector2f normalized_v = {0, 0};
    sfVector2f move_vector = {0, 0};

    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++) {
            handle_map_boundaries(w->corners[i]->ac[j]);
            v = w->corners[i]->ac[j]->vector;
            magnitude = sqrtf(v.x * v.x + v.y * v.y);
            normalized_v = (sfVector2f){v.x / magnitude, v.y / magnitude};
            move_vector = (sfVector2f){normalized_v.x *
                (w->corners[i]->ac[j]->speed / 60.0f), normalized_v.y *
                (w->corners[i]->ac[j]->speed / 60.0f)};
            sfRectangleShape_move(w->corners[i]->ac[j]->hitbox, move_vector);
            sfSprite_move(w->corners[i]->ac[j]->sprite, move_vector);
        }
    }
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
    static char *fps_str = "0";
    static char *second_str = "0";
    static int is_malloc = 0;

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
        if (is_malloc == 1) {
            free(fps_str);
            free(second_str);
            is_malloc = 0;
        }
        second++;
        fps_str = score_convert(fps);
        second_str = score_convert(second);
        is_malloc = 1;
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
    sfText_setString(w->fps, fps_str);
    sfRenderWindow_drawText(w->win, w->fps, NULL);
    sfText_setString(w->seconds, second_str);
    sfRenderWindow_drawText(w->win, w->seconds, NULL);
    sfRenderWindow_display(w->win);
}

int open_window(char **array)
{
    sfEvent event = {0};
    sfClock *clock = sfClock_create();
    window_t *w = init_window(array);
    sfText *text = init_text((sfVector2f){820, 0}, 40);

    sfText_setString(text, "FPS,\t\tSecond(s)");
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
