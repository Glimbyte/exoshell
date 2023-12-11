/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:27:48 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/11 12:43:48 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_home( t_env_map *map, char *path)
{
	char	*home;

	home = get_env(map, "HOME");
	if (home == NULL)
		return (0);
	strlcpy(path, home, PATH_MAX);
	free(home);
	return (1);
}

static int	get_oldpwd(t_env_map *map, char *new_pwd)
{
	char	*old_pwd;

	old_pwd = get_env(map, "PWD");
	if (old_pwd == NULL)
		return (0);
	strlcpy(new_pwd, old_pwd, PATH_MAX);
	free(old_pwd);
	return (1);
}

static void	newpwd_put(char *new_pwd, char s)
{
	int	n;

	n = 0;
	while (new_pwd[n] != '\0' && n < PATH_MAX)
		n++;
	new_pwd[n] = s;
}

static void	delete_last_dir(char *new_pwd)
{
	int	n;

	n = 0;
	while (new_pwd[n] != '\0')
		n++;
	while (new_pwd[n] != '/' && n != 0)
	{
		new_pwd[n] = '\0';
		n--;
	}
	new_pwd[n] = '\0';
}

static int new_pwd_maker(t_env_map *map, char *new_pwd, char *path)
{
	if (strncmp(path, ".", 1) == 0)
		if (get_oldpwd(map, new_pwd) == 0)
			return (0);
	if (strncmp(path, "/", 1) != 0)
	{
		if (get_oldpwd(map, new_pwd) == 0)
			return (0);
	}
	else
		path++;
	while (*path)
	{
		if (strncmp(path, "..", 2) == 0)
			delete_last_dir(new_pwd);
		if (*path != '/' && *path != '\0' && *path != '.')
			newpwd_put(new_pwd, '/');
		while (*path != '/' && *path != '\0' && *path != '.')
		{
			newpwd_put(new_pwd, *path);
			path++;
		}
		while (*path != '/' && *path != '\0')
			path++;
		while (*path == '/')
			path++;
	}
	return (1);
}

int	buildin_cd(t_command_exec	*cmd_exec)
{
	char	path[PATH_MAX];
	char	new_pwd[PATH_MAX];

	bzero(path, PATH_MAX);
	bzero(new_pwd, PATH_MAX);
	if (cmd_exec->argv[1] == NULL)
		if (get_home(cmd_exec->map, path) == 0)
			return (0);
	if (path[0] == 0)
		strlcpy(path, cmd_exec->argv[1], PATH_MAX);
	if (chdir(path) < 0)
		fatal_error("error cdfir <cd.c>\n");
	if (new_pwd_maker(cmd_exec->map, new_pwd, path) == 0)
		return (0);
	map_unset(cmd_exec->map, "PWD");
	if (map_set(cmd_exec->map, strdup("PWD"), strdup(new_pwd)) == 0)
		return (0);
	return (1);
}
