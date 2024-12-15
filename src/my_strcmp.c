/*
** EPITECH PROJECT, 2024
** delivery_2.0
** File description:
** my_strcmp
*/

/*
Compares the two strings s1 and s2
@param s1 string
@param s2 string
*/
int my_strcmp(char const *s1, char const *s2)
{
    for (int i = 0; s1[i] || s2[i]; i++) {
        if (s1[i] == s2[i])
            continue;
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}
