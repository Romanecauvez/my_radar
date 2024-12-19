/*
** EPITECH PROJECT, 2024
** day_13
** File description:
** main
*/

#include "window.h"

int print_h(void)
{
    write(1, "\tAir traffic simulation panel\n", 30);
    write(1, "USAGE\n", 6);
    write(1, "\t./my_radar [OPTIONS] path_to_script\n", 37);
    write(1, "\tpath_to_script The path to the script file.\n", 45);
    write(1, "OPTIONS\n", 9);
    write(1, "\t-h print the usage and quit.\n", 30);
    write(1, "USER INTERACTIONS\n", 18);
    write(1, "\t'L' key enable/disable hitboxes and areas.\n", 44);
    write(1, "\t'S' key enable/disable sprites.\n", 33);
    return 0;
}

char **parse_args(char *file_name)
{
    char *buff = NULL;
    char **array = NULL;
    struct stat s;
    int fd = 0;

    if (stat(file_name, &s) == -1)
        return NULL;
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        return NULL;
    buff = malloc(sizeof(char) * s.st_size + 1);
    if (read(fd, buff, s.st_size) == -1) {
        free(buff);
        return NULL;
    }
    buff[s.st_size] = '\0';
    close(fd);
    array = my_str_to_word_array(buff, "\n");
    free(buff);
    return array;
}

int main(int argc, char **argv)
{
    char **array = NULL;

    if (argc != 2)
        return 84;
    if (my_strcmp(argv[1], "-h") == 0)
        return print_h();
    array = parse_args(argv[1]);
    if (!array)
        return 84;
    return open_window(array);
}
