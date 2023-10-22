/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:09:08 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 18:41:04 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_cmd(t_node	*node)
{
	if (node->kind != SEQUENTIAL_CMD)
		fatal_error("not PIPE_CMD <exec_cmd.c>\n");
	exec_pipe(node->lhs);
	if (node->rhs != NULL)
		exec_pipe(node->rhs);
}
