/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-romane.cauvez
** File description:
** get_nb_towers_ac
*/

int get_nb_ac(char **array)
{
    int nb_ac = 0;

    for (int i = 0; array[i]; i++) {
        if (array[i][0] == 'A')
            nb_ac++;
    }
    return nb_ac;
}

int get_nb_to(char **array)
{
    int nb_to = 0;

    for (int i = 0; array[i]; i++) {
        if (array[i][0] == 'T')
            nb_to++;
    }
    return nb_to;
}
