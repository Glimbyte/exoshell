# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 18:00:19 by mfujimak          #+#    #+#              #
#    Updated: 2023/11/27 13:10:06 by mfujimak         ###   ########.fr        #
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

VPATH = src lib src/exec src/lexer src/expand src/parser src/cmd src/redir src/buildin

SRC := shell.c

SRC += exec_scmd.c exec_pipe.c exec_cmd.c exec.c exec_redirect.c

SRC += token.c

SRC += expand.c ft_substdio.c

SRC += redirect.c heredoc.c

SRC += parser.c

SRC += error.c

SRC += env_map.c

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

dot:
	 dot -Tpng -o parser.png parser.dot
	 code ./parser.png
