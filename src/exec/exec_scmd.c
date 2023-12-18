/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:09:08 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/18 13:33:17 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_scmd(t_node *node, t_env_map *env_map)
{
	t_command_exec *cmd_exec;

	if (node == NULL)
		return ;
	if (node->lhs == NULL)
		return ;
	cmd_exec = calloc(1, sizeof(t_command_exec));
	cmd_exec->map = env_map;
	cmd_exec->node = node;
	node = node->lhs;
	if (node->kind != SEQUENTIAL_CMD)
		fatal_error("not SEQUENTIAL_CMD <exec_cmd.c>\n");
	exec_pipe(node->lhs, cmd_exec);
	if (node->rhs != NULL)
		exec_scmd(node->rhs, env_map);
}

void	scmd_free(t_command_exec *cmd_exec)
{
	if (cmd_exec == NULL)
		return ;
	if (cmd_exec->node)
		node_free(cmd_exec->node);
	cmd_free(cmd_exec);
}

void	cmd_free(t_command_exec *cmd_exec)
{
	if (cmd_exec == NULL)
		return ;
	if (cmd_exec->next)
		cmd_free(cmd_exec->next);
	if (cmd_exec->argv)
		free(cmd_exec->argv);
	if (cmd_exec->path)
		free(cmd_exec->path);
	if (cmd_exec)
		free(cmd_exec);
}
