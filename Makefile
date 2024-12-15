##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my_ls
##

SRC	=	src/main.c			\
		src/open_window.c	\
		src/my_destroy.c	\
		src/init.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CFLAGS = -W -Wextra -Wall -Werror -I ./include -l csfml-graphics \
	-l csfml-system -l csfml-window -l csfml-audio

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all
