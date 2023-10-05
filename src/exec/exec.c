/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:37:02 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/03 20:11:26 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//this use fork, execve, wait

void	fatal_error(const char *msg)
{
	dprintf(1, "Fatal Error: %s\n", msg);
	exit(1);
}

int	exec(char *path)
{
	char		*argv[] = {path, NULL};
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
