/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:20:17 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/26 12:39:20 by mfujimak         ###   ########.fr       */
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
		new_line = strdup("\n");
		strcat(line, new_line);
		strcat(line, tmp_line);
	}
	return (line);
}

void	set_p_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->next != NULL)
		set_p_heredoc(redir->next);
}

void	set_c_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->next != NULL)
		set_c_heredoc(redir->next);
}

void	reset_p_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->next != NULL)
		reset_p_heredoc(redir->next);
}

void	reset_c_heredoc(t_redirect *redir)
{
	if (redir == NULL)
		return ;
	if (redir->next != NULL)
		reset_c_heredoc(redir->next);
}
