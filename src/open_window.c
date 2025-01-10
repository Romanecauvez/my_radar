/*
** EPITECH PROJECT, 2023
** open_window.c
** File description:
** open a window
*/

#include "window.h"

static int analyse_events(sfEvent *event, window_t *w)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
        return 1;
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyQ))
        sfRenderWindow_close(w->win);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
        w->state_s = !w->state_s;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyL)
        w->state_l = !w->state_l;
    return 0;
}

static void handle_map_boundaries(aircraft_t *ac)
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

static void ac_movement(window_t *w)
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

static int convert_fps_seconds(int is_malloc, char **fps_str,
    char **second_str, int fps)
{
    static int second = 0;

    if (is_malloc == 1) {
        free(fps_str);
        free(second_str);
        is_malloc = 0;
    }
    second++;
    *fps_str = score_convert(fps);
    *second_str = score_convert(second);
    is_malloc = 1;
    return second;
}

void display_text(window_t *w, char *fps_str, char *second_str)
{
    sfText_setString(w->fps, fps_str);
    sfRenderWindow_drawText(w->win, w->fps, NULL);
    sfText_setString(w->seconds, second_str);
    sfRenderWindow_drawText(w->win, w->seconds, NULL);
}

int clock_handeling(sfClock *clock, window_t *w)
{
    static int fps = 0;
    static int second = 0;
    static char *fps_str = "0";
    static char *second_str = "0";
    static int is_malloc = 0;
    sfTime elapsed = sfClock_getElapsedTime(clock);

    if (sfTime_asSeconds(elapsed) >= 1) {
        second = convert_fps_seconds(is_malloc, &fps_str, &second_str, fps);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
    display_text(w, fps_str, second_str);
    if (sfTime_asSeconds(elapsed) >= 0.016)
        ac_movement(w);
    return second;
}

int while_window_open(window_t *w, sfClock *clock)
{
    int second = 0;

    if (w->state_l == sfTrue)
        display_boundaries(w);
    if (w->state_s == sfTrue)
        display_sprites(w);
    for (int i = 0; w->corners[i]; i++) {
        for (int j = 0; w->corners[i]->ac[j]; j++) {
            is_intersecting_ac(w, j, i);
            is_arrived(w, w->corners[i]->ac[j]);
        }
    }
    second = clock_handeling(clock, w);
    sfRenderWindow_display(w->win);
    return second;
}

int display_window(window_t *w, sfText *text, int second, sfClock *clock)
{
    sfRenderWindow_clear(w->win, sfBlack);
    sfRenderWindow_drawSprite(w->win, w->bg, NULL);
    sfRenderWindow_drawText(w->win, text, NULL);
    for (int i = 0; w->corners[i]; i++)
        w->corners[i]->nb_ac = 0;
    w->corners = parse_in_corners(w, second);
    second = while_window_open(w, clock);
    return second;
}

int open_window(char **array)
{
    sfEvent event = {0};
    int second = 0;
    sfClock *clock = sfClock_create();
    window_t *w = init_window(array);
    sfText *text = init_text((sfVector2f){1550, 0}, 40);
    int esc_is_pressed = 0;

    sfText_setString(text, "FPS,\t\tSecond(s)");
    free_array(array);
    sfRenderWindow_setFramerateLimit(w->win, 60);
    while (sfRenderWindow_isOpen(w->win)) {
        while (sfRenderWindow_pollEvent(w->win, &event))
            esc_is_pressed += analyse_events(&event, w);
        if (esc_is_pressed % 2 == 0)
            second = display_window(w, text, second, clock);
        if (w->nb_ac == 0)
            sfRenderWindow_close(w->win);
    }
    sfClock_destroy(clock);
    return my_destroy(w);
}
