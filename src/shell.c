/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:01:24 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 14:50:35 by mfujimak         ###   ########.fr       */
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
	t_shell	input;

	shell_init();
	while (1)
	{
		input.line = readline("shell$ ");
		if (input.line == NULL)
			break ;
		if (*input.line)
			add_history(input.line);
		reader_loop(&input);
		free(input.line);
	}
	shell_end();
	exit(0);
}

void	reader_loop(t_shell *input)
{
	int		EOF_Reached;

	EOF_Reached = 0;
	while (EOF_Reached == 0)
	{
		reader_command(input);
		EOF_Reached = EOF;
	}
}

void	reader_command(t_shell *command)
{
	// char *line;
	t_token *tok;

	// tok = tokenize(line);
	// exec_main(tok);
	// exec_path(command->line);
	command->tok = tokenize(command->line);

	tok = command->tok;
	while (tok->kind != TK_EOF)
	{
		printf("token is >%s< \n", tok->word);
		tok = tok->next;
	}
	if (tok->kind == TK_EOF)
		printf("token_EOF\n");
}

void	shell_end(void)
{
	write_history(".minishell_history");
}
