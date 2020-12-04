# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmorimot <kmorimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/12 13:07:44 by kmorimot          #+#    #+#              #
#    Updated: 2020/12/04 19:49:14 by kmorimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_mini_ls
CC := gcc
CFLAGS := -Wall -Wextra -Werror
SRC_DIR := ./
SRCS := ft_mini_ls.c ft_lst_sort.c ft_mini_ls_utils.c ft_mini_ls_utils2.c
OBJS := $(SRCS:.c=.o)
INCLUDE := -I.ft_mini_ls.h \
	   -I./libft/libft.h

AR := ar
ARFLAGS := rcs

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	cp libft/libft.a .
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) libft.a

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean
	rm ./libft.a

re: fclean all

.PHONY: all clean fclean re
