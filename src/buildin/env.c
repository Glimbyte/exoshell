/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:01:38 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 19:31:47 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_env(t_command_exec	*cmd_exec)
{
	char **env;
	(void)cmd_exec;
	printf("buildin env \n");
	env = get_full_env(cmd_exec->map);
	while (*env)
	{
		printf ("%s\n", *env);
		env++;
	}
	return (1);
}
