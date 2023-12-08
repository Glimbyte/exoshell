/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:27:48 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/08 17:55:02 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
}

static char	*new_pwd_maker(char *new_pwd, char *old_pwd, char *path, char *home)
{
	return (new_pwd);
}

int	buildin_cd(t_command_exec	*cmd_exec)
{
	return (1);
}
