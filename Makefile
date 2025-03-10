##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my_radar
##

SRC	=	src/main.c			\
		src/my_destroy.c	\
		src/my_arraylen.c	\
		src/open_window.c	\
		src/my_str_isnum.c	\
		src/my_getnbr.c	\
		src/get_args.c	\
		src/my_strdup.c	\
		src/my_strlen.c	\
		src/my_strcmp.c	\
		src/init.c	\
		src/cmp.c	\
		src/get_nb_towers_ac.c	\
		src/my_str_to_word_array.c	\
		src/crash_destination_handeling.c	\
		src/displays.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CFLAGS	=	-W -Wextra -Wall -Werror -I ./include -l csfml-graphics \
	-l csfml-system -l csfml-window -l csfml-audio -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc src/parsing.c -o $(NAME) $(OBJ) $(CFLAGS)

bonus:	$(NAME) $(OBJ)
	gcc bonus/parse_bonus.c -o $(NAME) $(OBJ) $(CFLAGS)

debug:	$(NAME) $(OBJ)
	gcc src/parsing.c -o $(NAME) $(OBJ) $(CFLAGS) -g

exec_debug:
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all \
		./$(NAME) lot_of_ac.rdr 2>vgcore.out

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
