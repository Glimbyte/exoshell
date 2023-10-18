# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:00:19 by mfujimak          #+#    #+#              #
#    Updated: 2023/10/18 13:01:59 by mfujimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS    := -I./inc

LINK_LIB := -lreadline
ifeq ($(shell uname), Linux)
	LINK_LIB += -lbsd
endif

ifeq ($(shell uname), Darwin)
	# User have to run brew install readline before run make to build minishell
	CFLAGS += -I $(shell brew --prefix readline)/include
	LINK_LIB += -L$(shell brew --prefix readline)/lib
endif


OBJ_DIR ?= ./obj
SRC_DIRS ?= ./src
LIB_DIR ?= ./lib
HEADER_DIR ?= ./inc

VPATH = src lib src/exec src/lexer src/expand src/parser

SRC := shell.c

SRC += exec.c exec_path.c exec_token.c exec_cmd.c

SRC += token.c

SRC += expand.c ft_substdio.c

SRC += parser.c

SRC += error.c

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADER := $(shell find $(HEADER_DIR) -name \*.h)

.PHONY: all clean fclean re test

all :$(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC)  $(CPPFLAGS) $(OBJ) -o $@ $(LINK_LIB)

clean :
	rm -r $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	@cd ./test && bash test_tmp.sh

norm:
	norminette
