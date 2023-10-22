/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:02 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 18:43:21 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	exec(char *path, char **argv)
{
	extern char	**environ;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0) // child process
		execve(path, argv, environ);
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (0);
}
