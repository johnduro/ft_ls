# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: johnduro <>                                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/28 11:39:35 by johnduro          #+#    #+#              #
#    Updated: 2014/01/28 11:39:35 by johnduro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
VERSION=1.0.0
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes -L /usr/lib
LIBS=./libft/libft.a

SRC=ft_ls.c \
    initLs.c \
    debugLs.c \
    freeLs.c \
    infosLS.c

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ)
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c ft_ls.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $< -L /usr/lib

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all build clean fclean re v
