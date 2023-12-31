/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:34 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/07 13:35:15 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
// #include <bsd/string.h>

//exec.c
#include "ft_subbool.h"
#include "ft_substdio.h"
#include "error.h"
#include "token.h"
#include "parser.h"
#include "env.h"
#include "redirect.h"
#include "exec.h"
#include "expand.h"
#include "buildin.h"

typedef struct struct_shell
{
	char	*line;
	t_token	*tok;
	t_node	*node;
	t_env_map	env_map;
}			t_shell;

// char *readline(const char *prompt)
// void using_history(void)
// void add_history(const char *string)
// int read_history(const char *filename)
// int write_history(const char *filename)

void		shell_init(t_shell *command);
void		reader_loop(t_shell *input);
void		shell_end(void);
