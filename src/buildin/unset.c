/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:01:40 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 19:55:25 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_unset(t_command_exec	*cmd_exec)
{
	int	n;

	(void)cmd_exec;
	printf("buildin unset\n");
	n = 1;
	while (cmd_exec->argv[n] != NULL)
	{
		if (!map_unset(cmd_exec->map, cmd_exec->argv[n]))
			fatal_error("cant fine set_env<buildin_unset.c\n>");
		n++;
	}
	return (1);
}
