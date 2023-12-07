/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:28:07 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 20:13:01 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	export_printf(t_env_map *map)
{
	t_env_item *tmp;

	tmp = map->first_item;
	while (tmp)
	{
		printf ("declare -x %s=", tmp->name);
		if (tmp->value)
			printf ("\"%s\" \n", tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

int	buildin_export(t_command_exec	*cmd_exec)
{
	(void)cmd_exec;
	int	n;
	printf("buildin export\n");
	if (cmd_exec->argv[1] == NULL)
		return (export_printf(cmd_exec->map));
	n = 1;
	while (cmd_exec->argv[n] != NULL)
	{
		if (!map_put(cmd_exec->map, cmd_exec->argv[n]))
			return (0);
		n++;
	}
	map_view(cmd_exec->map);
	return (1);
}
