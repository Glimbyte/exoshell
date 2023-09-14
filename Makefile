# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:00:19 by mfujimak          #+#    #+#              #
#    Updated: 2023/09/14 18:13:38 by mfujimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR ?= ./obj
SRC_DIRS ?= ./src
LIB_DIR ?= ./lib
HEADER_DIR ?= ./include

SRC := $(shell find $(SRC_DIRS) -name \*.c)
OBJ := $(SRC:%=$(OBJ_DIR)/%.o)
HEADER := $(shell find $(HEADER_DIR) -name \*.h)

$(OBJ_DIR)/%.c.o: %.c
    $(MKDIR_P) $(dir $@)
    $(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all :$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean :
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

MKDIR_P ?= mkdir –p