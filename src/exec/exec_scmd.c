/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:09:08 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/02 14:21:37 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_scmd(t_node *node, t_env_map *env_map)
{
	if (node == NULL)
		return ;
	if (node->kind != SEQUENTIAL_CMD)
		fatal_error("not SEQUENTIAL_CMD <exec_cmd.c>\n");
	t_command_exec *cmd_exec;

	cmd_exec = calloc(1, sizeof(t_command_exec));
	cmd_exec->map = env_map;
	exec_pipe(node->lhs, cmd_exec);
	if (node->rhs != NULL)
		exec_scmd(node->rhs, env_map);
}
