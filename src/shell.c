/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:24 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/18 13:42:59 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shell_init(t_shell *command)
{
	extern char	**environ;

	rl_outstream = stderr;
	using_history();
	read_history(".minishell_history");
	map_init(&command->env_map, environ);
	map_view(&command->env_map);
}

int	main(void)
{
	t_shell	command;

	shell_init(&command);
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
		command->tok = tokenize(command->line); //malloc OK
		token_check(command->tok); //check protocol
		command->node = parser(command->tok); //malloc OK
		parser_check( "parser.dot", command->node); //check protpcol
		expand(command->node);
		EOF_Reached = EOF;
	}
	if (command->node != NULL)
		exec_scmd(command->node, &command->env_map);
}

void	shell_end(void)
{
	write_history(".minishell_history");
}
