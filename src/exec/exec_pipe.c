/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:25:30 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/25 15:45:33 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_pipe(t_node	*node, t_command_exec	*cmd_exec)
{
	if (node->kind != PIPE_CMD)
		fatal_error("not PIPE_CMD <exec_cmd.c>\n");
	if (node->rhs != NULL)
	{
		cmd_exec->next = calloc(1, sizeof(t_command_exec));
		prepare_p_pipe(cmd_exec);
		exec_cmd (node->lhs, cmd_exec);
		exec_pipe(node->rhs, cmd_exec->next);
	}
	else
		exec_cmd (node->lhs, cmd_exec);
	wait(NULL);
}

void	prepare_p_pipe(t_command_exec	*cmd_exec)
{
	pipe(cmd_exec->output_pipe);
	cmd_exec->next->input_pipe[0] = cmd_exec->output_pipe[0];
	cmd_exec->next->input_pipe[1] = cmd_exec->output_pipe[1];
}

void	end_p_pipe(t_command_exec	*cmd_exec)
{
	if (cmd_exec->input_pipe[0] != 0)
	{
		close(cmd_exec->input_pipe[0]);
		close(cmd_exec->input_pipe[1]);
	}
}


void	prepare_c_pipe(t_command_exec	*cmd_exec)
{
	if (cmd_exec->input_pipe[0] != 0)
	{
		close(cmd_exec->input_pipe[1]);
		dup2(cmd_exec->input_pipe[0], STDIN_FILENO);
	}
	if (cmd_exec->output_pipe[0] != 0)
	{
		close(cmd_exec->output_pipe[0]);
		dup2(cmd_exec->output_pipe[1], STDOUT_FILENO);
	}
}

void	end_c_pipe(t_command_exec	*cmd_exec)
{
	if (cmd_exec->input_pipe[1] != 0)
	{
		close(cmd_exec->input_pipe[0]);
	}
	if (cmd_exec->output_pipe[0] != 0)
	{
		close(cmd_exec->output_pipe[1]);
	}
}
