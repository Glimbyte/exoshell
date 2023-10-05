/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:34 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/03 17:47:48 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//exec.c
#include "exec.h"

// char *readline(const char *prompt)
// void using_history(void)
// void add_history(const char *string)
// int read_history(const char *filename)
// int write_history(const char *filename)

typedef struct struct_shell
{
	char	*line;
}			s_shell;

void		shell_init(void);
void		reader_loop(s_shell *input);
void		reader_command(s_shell *input);
void		shell_end(void);
