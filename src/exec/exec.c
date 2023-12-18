/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:02 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/13 09:23:09 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exec(t_command_exec	*cmd_exec)
{
	set_p_heredoc(cmd_exec->refirection);
	cmd_exec->pid = fork();
	if (cmd_exec->pid < 0)
		fatal_error("fork");
	else if (cmd_exec->pid == 0)
	{
		prepare_c_pipe(cmd_exec);
		set_redirect(cmd_exec->refirection);
		set_c_heredoc(cmd_exec->refirection);
		execve(cmd_exec->path, cmd_exec->argv, get_full_env(cmd_exec->map));
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

int	exec_buildin(t_command_exec	*cmd_exec)
{
	set_p_heredoc(cmd_exec->refirection);
	prepare_c_pipe(cmd_exec);
	set_redirect(cmd_exec->refirection);
	set_c_heredoc(cmd_exec->refirection);
	buildin_cmd(cmd_exec);
	reset_c_heredoc(cmd_exec->refirection);
	reset_redirect(cmd_exec->refirection);
	end_p_pipe(cmd_exec);
	return (0);
}
