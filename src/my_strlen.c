/*
** EPITECH PROJECT, 2024
** my_libC
** File description:
** my_strlen
*/

/*
Returns the length of the given string
@param str string
*/
int my_strlen(char *str)
{
    int i = 0;

    if (!str)
        return -1;
    while (str[i])
        i++;
    return i;
}
