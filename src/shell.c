/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:24 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/03 21:10:17 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shell_init(void)
{
	rl_outstream = stderr;
	using_history();
	read_history(".minishell_history");
}

int	main(void)
{
	t_shell	command;

	shell_init();
	while (1)
	{
		command.line = readline("shell$ ");
		if (command.line == NULL)
			break ;
		if (*command.line)
			add_history(command.line);
		reader_loop(&command);
		free(command.line);
	}
	shell_end();
	exit(0);
}

void	reader_loop(t_shell *command)
{
	int		EOF_Reached;

	EOF_Reached = 0;
	while (EOF_Reached == 0)
	{
		command->tok = tokenize(command->line);
		token_check(command->tok); //check protocol
		command->node = parser(command->tok);
		parser_check( "parser.dot", command->node); //check protpcol
		expand(command);
		EOF_Reached = EOF;
	}
	exec_scmd(command->node->lhs);
}

void	reader_command(t_shell *command)
{
	(void)command;
}

void	shell_end(void)
{
	write_history(".minishell_history");
}

#include <semaphore.h>
#include <pthread.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}
