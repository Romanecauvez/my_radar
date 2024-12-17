/*
** EPITECH PROJECT, 2024
** B-CPE-101-LIL-1-1-myprintf-romane.cauvez
** File description:
** my_strdup
*/

#include "window.h"

char *my_strdup(char const *src)
{
    int len = 0;
    char *dup = NULL;
    int i = 0;

    if (!src)
        return NULL;
    len = my_strlen((char *)src);
    dup = malloc(sizeof(char) * (len + 1));
    for (; i < len; i++)
        dup[i] = src[i];
    dup[i] = '\0';
    return dup;
}
