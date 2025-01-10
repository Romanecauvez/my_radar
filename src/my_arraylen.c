/*
** EPITECH PROJECT, 2024
** my_libC
** File description:
** my_arraylen
*/

/*
Returns the length of the given array
@param str string
*/
int my_arraylen(char **str)
{
    int i = 0;

    for (; str[i]; i++);
    return i;
}
