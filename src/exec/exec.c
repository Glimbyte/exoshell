/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:02 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/02 03:11:15 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exec(t_command_exec	*cmd_exec)
{
	extern char	**environ;

	set_p_heredoc(cmd_exec->refirection);
	cmd_exec->pid = fork();
	if (cmd_exec->pid < 0)
		fatal_error("fork");
	else if (cmd_exec->pid == 0)
	{
		prepare_c_pipe(cmd_exec);
		set_redirect(cmd_exec->refirection);
		set_c_heredoc(cmd_exec->refirection);
		execve(cmd_exec->path, cmd_exec->argv, environ);
		reset_c_heredoc(cmd_exec->refirection);
		reset_redirect(cmd_exec->refirection);
		end_c_pipe(cmd_exec);
		exit(1);
	}
	do_p_heredoc(cmd_exec->refirection);
	reset_p_heredoc(cmd_exec->refirection);
	end_p_pipe(cmd_exec);
	return (0);
}
