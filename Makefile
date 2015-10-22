# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroche <vroche@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/13 14:30:49 by vroche            #+#    #+#              #
#    Updated: 2015/10/22 19:27:50 by vroche           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = -L./libft -lft -lreadline

HDR = -I./libft/includes

FLAG = -Wall -Wextra -Werror -g

C = ft_cd.c \
	ft_env.c \
	ft_execve.c \
	ft_isexec.c \
	ft_manage.c \
	ft_setenv.c \
	ft_spacesplit.c \
	main.c

O = $(C:%.c=%.o)

all: $(NAME)

$(NAME): $(O)
	make -C ./libft
	gcc $(FLAG) $(LIB) $(HDR) $(O) -o $(NAME)

%.o:%.c
	gcc $(FLAG) $(HDR) -c $<

clean:
	make -C ./libft clean
	rm -f $(O)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
