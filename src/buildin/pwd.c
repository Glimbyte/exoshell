/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:28:14 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 19:37:06 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_pwd(t_command_exec	*cmd_exec)
{
	char	*pwd;
	char	cwd[PATH_MAX];
	(void)cmd_exec;
	printf("buildin pwd\n");

	pwd = get_env(cmd_exec->map, "PWD");
	if (pwd != NULL)
		printf("%s\n", pwd);
	if (getcwd(cwd, PATH_MAX) == NULL)
		fatal_error("cant get pwd <buildin_pwd.c>\n");
	return (1);
}
