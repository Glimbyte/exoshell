/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:27:56 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/11 13:25:40 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_echo(t_command_exec	*cmd_exec)
{
	(void)cmd_exec;

	if (cmd_exec->argv[1] == NULL)
		return (1);
	if (strncmp(cmd_exec->argv[1], "-n", 2) == 0)
		return (write(1, cmd_exec->argv[2], strlen(cmd_exec->argv[2])));
	else
		write(1, cmd_exec->argv[1], strlen(cmd_exec->argv[1]));
	write(1, "\n", 1);
	return (1);
}
