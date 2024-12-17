/*
** EPITECH PROJECT, 2024
** delivery_2.0
** File description:
** my_str_to_word_array
*/

#include "window.h"

static int char_contains(char c, char *delimiter)
{
    for (int i = 0; delimiter[i] != '\0'; i++)
        if (c == delimiter[i])
            return 1;
    return 0;
}

static int count_words(char *s, char *delimiter)
{
    int words_count = 0;

    if (!s)
        return 0;
    for (int x = 0; s[x] != '\0'; x++) {
        if (!char_contains(s[x], delimiter)
            && (char_contains(s[x + 1], delimiter) || s[x + 1] == '\0'))
            words_count++;
    }
    return (words_count);
}

static void fill_array(const char *s, char *delimiter, char **word_array
    , int word_count)
{
    int i = 0;
    int start_of_word = 0;
    int word_len = 0;

    for (int row = 0; word_count > row; row++) {
        for (; s[i] != '\0' && char_contains(s[i], delimiter); i++);
        start_of_word = i;
        for (; s[i] != '\0' && !char_contains(s[i], delimiter); i++);
        word_len = i - start_of_word;
        word_array[row] = malloc(sizeof(char) * (word_len + 1));
        for (int y = 0; y < word_len; y++)
            word_array[row][y] = s[y + start_of_word];
        word_array[row][word_len] = '\0';
    }
}

/*
Creates an array with a delimiter in a string
@param str string
*/
char **my_str_to_word_array(char *s, char *delimiter)
{
    char **word_array = NULL;
    int word_count = count_words(s, delimiter);

    if (word_count == 0 || !s) {
        return NULL;
    }
    if (!delimiter) {
        word_array = malloc(sizeof(char *) * 1 + 1);
        word_array[0] = my_strdup(s);
        return word_array;
    }
    word_array = malloc(sizeof(char *) * (word_count + 1));
    fill_array(s, delimiter, word_array, word_count);
    word_array[word_count] = NULL;
    return word_array;
}
