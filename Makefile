# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:00:19 by mfujimak          #+#    #+#              #
#    Updated: 2023/09/15 01:48:55 by mfujimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS    := -I./include

OBJ_DIR ?= ./obj
SRC_DIRS ?= ./src
LIB_DIR ?= ./lib
HEADER_DIR ?= ./include

VPATH = src lib

SRC := shell.c
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADER := $(shell find $(HEADER_DIR) -name \*.h)

.PHONY: all clean fclean re test

all :$(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC)  $(CPPFLAGS) $(OBJ) -o $@

clean :
	rm -r $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	@cd ./test && bash test.sh

norm:
	norminette
