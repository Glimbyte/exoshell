/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:04:57 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/12 13:07:18 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//this use acsecc, getenv

void	exec_path(char *path)
{
	if(path == strchr(path, '/'))
		exec(path);
	else
	{
		path = exec_search_pash(path);
		if (path == NULL)
			fatal_error("can not find path <exec_serch_path>");
		exec(path);
		free(path);
	}
}

char	*exec_search_pash(const char *file)
{
	int		n;
	char	*path;
	char	*end_p;
	char	tmp_value[PATH_MAX];
	char	*re;

	path = getenv("PATH");
	if (path == NULL)
		fatal_error("can not get env");
	bzero(tmp_value,PATH_MAX);
	end_p = strchr(path, ':');
	while (end_p != NULL)
	{
		n = 0;
		while(end_p != path)
			tmp_value[n++] = *path++;
		strlcat(tmp_value, "/", PATH_MAX);
		strlcat(tmp_value, file, PATH_MAX);
		if (access(tmp_value, X_OK) == 0)
		{
			re = strdup(tmp_value);
			return (re);
		}
		bzero(tmp_value,PATH_MAX);
		path++;
		end_p = strchr(path, ':');
	}
	return (NULL);
}
