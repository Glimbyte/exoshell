/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:10:10 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 18:42:17 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	buildin_exit(t_command_exec	*cmd_exec)
{
	(void)cmd_exec;
	printf("buildin exit \n");
	exit(255);
}
