/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:38:57 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/02 14:50:23 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_cmd(t_command_exec	*cmd_exec)
{
	if (strncmp(cmd_exec->path, "cd", 2) == 0)
		return (buildin_cd(cmd_exec));
	else if (strncmp(cmd_exec->path, "echo", 4) == 0)
		return (buildin_echo(cmd_exec));
	else if (strncmp(cmd_exec->path, "env", 3) == 0)
		return (buildin_env(cmd_exec));
	else if (strncmp(cmd_exec->path, "exit", 4) == 0)
		return (buildin_exit(cmd_exec));
	else if (strncmp(cmd_exec->path, "export", 6) == 0)
		return (buildin_export(cmd_exec));
	else if (strncmp(cmd_exec->path, "pwd", 3) == 0)
		return (buildin_pwd(cmd_exec));
	else if (strncmp(cmd_exec->path, "unset", 5) == 0)
		return (buildin_unset(cmd_exec));
	return (0);
}

int	buildin_checker(char *filename)
{
	if (strncmp(filename, "cd", 2) == 0)
		return (1);
	else if (strncmp(filename, "echo", 4) == 0)
		return (1);
	else if (strncmp(filename, "env", 3) == 0)
		return (1);
	else if (strncmp(filename, "exit", 4) == 0)
		return (1);
	else if (strncmp(filename, "export", 6) == 0)
		return (1);
	else if (strncmp(filename, "pwd", 3) == 0)
		return (1);
	else if (strncmp(filename, "unset", 5) == 0)
		return (1);
	return (0);
}