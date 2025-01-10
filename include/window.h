/*
** EPITECH PROJECT, 2023
** delivery
** File description:
** hunter.h
*/


#ifndef WINDOW_H
    #define WINDOW_H
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Window/WindowBase.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Window/Event.h>
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <math.h>
    #include <sys/stat.h>

typedef struct aircraft_s {
    sfVector2f pos;
    sfVector2f a_pos;
    unsigned int delay;
    unsigned int speed;
    sfVector2f vector;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
} aircraft_t;

typedef struct tower_s {
    sfVector2f pos;
    sfSprite *sprite;
    sfCircleShape *area;
} tower_t;

typedef struct corner_s {
    unsigned int nb_ac;
    aircraft_t **ac;
} corner_t;

typedef struct window_s {
    corner_t **corners;
    tower_t **all_to;
    aircraft_t **all_ac;
    sfRenderWindow *win;
    sfSprite *bg;
    unsigned int nb_ac;
    sfBool state_s;
    sfBool state_l;
    sfText *seconds;
    sfText *fps;
} window_t;

int my_strlen(char *str);
int my_arraylen(char **str);
int free_array(char **array);
int my_getnbr(char const *str);
char *my_strdup(char const *src);
int my_str_isnum(char const *str);
int my_strcmp(char const *s1, char const *s2);
char **my_str_to_word_array(char *s, char *delimiter);
int open_window(char **array);
sfVector2i get_nb_ac_to(char **array);
window_t *init_window(char **array);
sfText *init_text(sfVector2f position, int size);
tower_t *init_tower(char **array, sfTexture *texture);
aircraft_t *init_aircraft(char **array, sfTexture *texture);
void parse_ac_to_infos(char **infos, window_t *w, sfTexture *ac_texture,
    sfTexture *to_texture);
corner_t **parse_in_corners(window_t *w, int second);
int ac_cmp(aircraft_t *ac1, aircraft_t *ac2);
void is_intersecting_ac(window_t *w, int j, int i);
void is_arrived(window_t *w, aircraft_t *ac);
void display_boundaries(window_t *w);
void display_sprites(window_t *w);
int my_destroy(window_t *w);

#endif
