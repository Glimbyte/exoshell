/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:38:57 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 18:36:00 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_cmd(t_command_exec	*cmd_exec)
{
	int	n;

	n = buildin_checker(cmd_exec->argv[0]);
	if (n == 1)
		return (buildin_cd(cmd_exec));
	else if (n == 2)
		return (buildin_echo(cmd_exec));
	else if (n == 3)
		return (buildin_env(cmd_exec));
	else if (n == 4)
		return (buildin_exit(cmd_exec));
	else if (n == 5)
		return (buildin_export(cmd_exec));
	else if (n == 6)
		return (buildin_pwd(cmd_exec));
	else if (n == 7)
		return (buildin_unset(cmd_exec));
	return (0);
}

int	buildin_checker(char *filename)
{
	if (strncmp(filename, "cd", 2) == 0)
		return (1);
	else if (strncmp(filename, "echo", 4) == 0)
		return (2);
	else if (strncmp(filename, "env", 3) == 0)
		return (3);
	else if (strncmp(filename, "exit", 4) == 0)
		return (4);
	else if (strncmp(filename, "export", 6) == 0)
		return (5);
	else if (strncmp(filename, "pwd", 3) == 0)
		return (6);
	else if (strncmp(filename, "unset", 5) == 0)
		return (7);
	return (0);
}
