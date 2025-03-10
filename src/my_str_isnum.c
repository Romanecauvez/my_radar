/*
** EPITECH PROJECT, 2024
** delivery_2.0
** File description:
** my_str_is_alpha
*/

/*
Verifies if every characters of a string are numeric
@param str string
*/
int my_str_isnum(char const *str)
{
    int i = 0;

    if (!str)
        return 1;
    if (str[0] == '-')
        i = 1;
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}
