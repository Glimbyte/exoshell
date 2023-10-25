/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_scmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:09:08 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/24 09:59:27 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_scmd(t_node	*node)
{
	if (node->kind != SEQUENTIAL_CMD)
		fatal_error("not SEQUENTIAL_CMD <exec_cmd.c>\n");
	t_command_exec *cmd_exec;

	cmd_exec = calloc(1, sizeof(t_command_exec));
	exec_pipe(node->lhs, cmd_exec);
	if (node->rhs != NULL)
		exec_scmd(node->rhs);
}
