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

typedef struct aircraft_s {
    sfVector2f pos;
    sfVector2f vector;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    unsigned int delay;
    unsigned int speed;
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

// sfBool is_clicked(button_t *button, sfMouseButtonEvent *event);
// sfBool is_hover(button_t *button, sfMouseMoveEvent *event);
// int open_window(void);
// sfCircleShape *init_circle(sfVector2f position, float radius);
// sfCircleShape **init_circles(int nbr_circle, sfVector2f position);
corner_t **init_corners(aircraft_t **ac, int nb_ac);
aircraft_t **init_aircrafts_tab(sfTexture *texture, int nb_ac);
void my_destroy(sfRenderWindow *window, sfCircleShape **circles);
int open_entry_window(void);
#endif
