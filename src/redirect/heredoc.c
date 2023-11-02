/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:20:17 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/02 03:38:01 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *heredoc(char *delimiter)
{
	char	*line;
	char	*tmp_line;
	char	*new_line;

	line = calloc(1, sizeof(char) * 1);
	while (1)
	{
		tmp_line = readline("> ");
		if (strcmp(tmp_line, delimiter) == 0)
		{
			free(tmp_line);
			break ;
		}
		strcat(line, tmp_line);
		new_line = strdup("\n");
		strcat(line, new_line);
	}
	return (line);
}

void	set_p_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RK_HEREDOC)
		pipe(redir->heredoc_pipe);
	if (redir->next != NULL)
		set_p_heredoc(redir->next);
}

void	set_c_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RK_HEREDOC)
	{
		close(redir->heredoc_pipe[1]);
		dup2(redir->heredoc_pipe[0], STDIN_FILENO);
	}
	if (redir->next != NULL)
		set_c_heredoc(redir->next);
}

void	do_p_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RK_HEREDOC)
	{
		close(redir->heredoc_pipe[0]);
		write(redir->heredoc_pipe[1], redir->filename, strlen(redir->filename));
	}
	if (redir->next != NULL)
		do_p_heredoc(redir->next);
}

void	reset_p_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RK_HEREDOC)
		close(redir->heredoc_pipe[1]);
	if (redir->next != NULL)
		reset_p_heredoc(redir->next);
}

void	reset_c_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == RK_HEREDOC)
		close(redir->heredoc_pipe[0]);
	if (redir->next != NULL)
		reset_c_heredoc(redir->next);
}
