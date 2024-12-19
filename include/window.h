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
    #include <stdio.h>
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

typedef struct window_s
{
    corner_t **corners;
    tower_t **all_to;
    unsigned int nb_ac;
    sfBool state_s;
    sfBool state_l;
} window_t;


// sfBool is_clicked(button_t *button, sfMouseButtonEvent *event);
// sfBool is_hover(button_t *button, sfMouseMoveEvent *event);
// int open_window(void);
// sfCircleShape *init_circle(sfVector2f position, float radius);
// sfCircleShape **init_circles(int nbr_circle, sfVector2f position);
int my_strlen(char *str);
void free_array(char **array);
int my_getnbr(char const *str);
char *my_strdup(char const *src);
int my_strcmp(char const *s1, char const *s2);
char **my_str_to_word_array(char *s, char *delimiter);
corner_t **init_corners(aircraft_t **ac, int nb_ac);
window_t *init_window(char **array, aircraft_t **all_ac);
tower_t **init_towers_tab(sfTexture *texture, char **infos);
aircraft_t **init_aircrafts_tab(sfTexture *texture, char **infos);
corner_t **parse_in_corners(aircraft_t **ac, int nb_ac, corner_t **corners);
int get_nb_ac(char **array);
int get_nb_to(char **array);
int open_window(char **array);
// void my_destroy(sfRenderWindow *window, sfCircleShape **circles);

#endif
