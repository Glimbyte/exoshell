/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 20:04:57 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/03 21:30:28 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>

//this use acsecc, getenv

char	*exec_search_pash(const char *file)
{
	int		n;
	char	*path;
	char	*end_p;
	char	tmp_value[PATH_MAX];
	char	*re;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);
	bzero(tmp_path,PATH_MAX);
	end_p = strchr(path, ':')
	while (end_p != NULL)
	{
		n = 0;
		while(end_p != path)
			tmp_value[++n] = *++path;
		strlcat(tmp_value, "/", PATH_MAX);
		strlcat(tmp_value, file, PATH_MAX);
		if (acsecc(tmp_value, X_OK) == 0)
		{
			re = strdup(tmp_value);
			free(path);
			return (re);
		}
		bzero(tmp_path,PATH_MAX);
		end_p = strchr(path, ':');
	}
	free(path);
	return (NULL);
}
