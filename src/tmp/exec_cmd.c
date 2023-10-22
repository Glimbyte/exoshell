/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 01:59:19 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 12:40:22 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_cmd(char *path, char *str)
{
	char *argv[3];
	argv[0] = path;
	argv[1] = str;
	argv[2] = NULL;
	exec_path(path, argv);
	//TODO free argv
}
