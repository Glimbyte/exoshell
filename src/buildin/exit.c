/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:10:10 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/26 15:46:44 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	buildin_exit(char **argv)
{
	long	re;
	char	*endptr;

	if (argv[1] == NULL)
		exit();
	if (argv[2] != NULL)
		fatal_error("too many argment <exit.c>\n");
	if (isdigit(argv[1]))
	{
		re = strtol(argv[1], endptr, 10);
		if (endptr == '\0')
			exit((int)re);
	}
	exit(255);
}
