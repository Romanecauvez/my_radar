/*
** EPITECH PROJECT, 2024
** bs_initiation
** File description:
** management
*/

#include "window.h"

static void manage_click(sfEvent event, struct button_s *button)
{
    if (event.type == sfEvtMouseButtonPressed) {
        if (is_clicked(button, &event.mouseButton))
            my_putstr("Hello\n");
    }
}

static void manage_hover(sfEvent event, button_t *button)
{
    if (event.type == sfEvtMouseMoved) {
        if (is_hover(button, &event.mouseMove))
            sfRectangleShape_setFillColor(button->square, sfBlack);
    }
}

void management(sfEvent event, button_t **buttons, int nb)
{
    for (int i = 0; i < nb; i++) {
        manage_click(event, buttons[i]);
        manage_hover(event, buttons[i]);
    }
}
