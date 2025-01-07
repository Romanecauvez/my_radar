/*
** EPITECH PROJECT, 2023
** open_window.c
** File description:
** open a window
*/

#include "window.h"

static void analyse_events(sfEvent *event, window_t *w)
{
    if (event->type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyQ) ||
        w->nb_ac == 0)
        sfRenderWindow_close(w->win);
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyS)
        w->state_s = !w->state_s;
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyL)
        w->state_l = !w->state_l;
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

static void convert_fps_seconds(int is_malloc, char **fps_str,
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
}

void clock_handeling(sfClock *clock, window_t *w)
{
    static int fps = 0;
    static char *fps_str = "0";
    static char *second_str = "0";
    static int is_malloc = 0;
    sfTime elapsed = sfClock_getElapsedTime(clock);

    if (sfTime_asSeconds(elapsed) >= 1) {
        convert_fps_seconds(is_malloc, &fps_str, &second_str, fps);
        fflush(stdout);
        fps = 0;
        sfClock_restart(clock);
    } else
        fps++;
    sfText_setString(w->fps, fps_str);
    sfRenderWindow_drawText(w->win, w->fps, NULL);
    sfText_setString(w->seconds, second_str);
    sfRenderWindow_drawText(w->win, w->seconds, NULL);
}

void while_window_open(sfEvent event, window_t *w, sfClock *clock)
{
    while (sfRenderWindow_pollEvent(w->win, &event))
        analyse_events(&event, w);
    if (w->state_l == sfTrue)
        display_boundaries(w);
    if (w->state_s == sfTrue)
        display_sprites(w);
    ac_movement(w);
    clock_handeling(clock, w);
    sfRenderWindow_display(w->win);
}

int open_window(char **array)
{
    sfEvent event = {0};
    sfClock *clock = sfClock_create();
    window_t *w = init_window(array);
    sfText *text = init_text((sfVector2f){1550, 0}, 40);

    sfText_setString(text, "FPS,\t\tSecond(s)");
    free_array(array);
    sfRenderWindow_setFramerateLimit(w->win, 60);
    while (sfRenderWindow_isOpen(w->win)) {
            sfRenderWindow_clear(w->win, sfBlack);
            sfRenderWindow_drawSprite(w->win, w->bg, NULL);
            sfRenderWindow_drawText(w->win, text, NULL);
            for (int i = 0; w->corners[i]; i++)
                w->corners[i]->nb_ac = 0;
            w->corners = parse_in_corners(w->all_ac, w->nb_ac, w->corners);
            while_window_open(event, w, clock);
    }
    sfClock_destroy(clock);
    my_destroy(w);
    return 0;
}
// int esc_is_pressed = 0;
// if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
//     esc_is_pressed = 1;
// if (esc_is_pressed == 0) {
