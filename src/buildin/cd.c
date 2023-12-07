/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:27:48 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/07 13:32:59 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	delete_last_dir(char *new_pwd)
{
	int	n;

	n = 0;
	while (new_pwd[n] != '\0')
		n++;
	while (new_pwd[n] != '/' && n != 0)
	{
		new_pwd[n] = '\0';
		n++;
	}
}

static char	*new_pwd_maker(char *new_pwd, char *old_pwd, char *path, char *home)
{
	if (strncmp(path, "~", 1))
		strlcop(new_pwd, home, PATH_MAX);
	else if (strncmp(path, "..", 2))
	{
		strlcop(new_pwd, old_pwd, PATH_MAX);
		delete_last_dir(new_pwd, path);
	}
	else if (strncmp(path, ".", 1))
		strlcop(new_pwd, old_pwd, PATH_MAX);
	path++;
	while (*path)
	{
		while (*path != '/')
			path++;
		path++;
		if (strncmp(path, "..", 2))
			delete_last_dir(new_pwd, path);
		else if (strncmp(path, ".", 1))
			;
		else
		{
			n = 0;
			while (new_pwd[n] != '\0')
				n++;
			while (*path != '/' && *path != '\0')
			{
				new_pwd[n] = *path;
				n++;
				path++;
			}
			new_pwd[n] = '/';
		}
	}
}

int	buildin_cd(t_command_exec	*cmd_exec)
{
	char	*home;
	char	path[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*old_pwd;
	(void)cmd_exec;
	printf("buildin cd \n");

	bzero(new_pwd);
	bzero(path);
	if (cmd_exec->argv[1] == NULL)
	{
		home = get_env(cmd_exec->map, "HOME")
		if (home)
			return (0);
		strlcop(path, home, PATH_MAX);
	}
	else
		strlcop(path, cmd_exec->argv[1], PATH_MAX);
	if (chdir(path) < 0)
		fatal_error("chdir cant work <cd.c>\n");
	old_pwd = get_env(cmd_exec->map, "PWD")
	if (old_pwd)
		return (0);
	new_pwd_maker(&new_pwd, old_pwd, &path, home);
	map_set(cmd_exec->map, now_pwd);
	free(old_pwd);
	free(home);
	return (1);
}
