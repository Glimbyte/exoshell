/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 01:59:19 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/13 03:21:52 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_cmd(char *path, t_token *tok)
{
	char *argv[3];
	argv[0] = path;
	argv[1] = exec_token(tok);
	argv[2] = NULL;
	printf("%s %s %s\n", argv[0], argv[1], argv[2]);
	exec_path(path, argv);
	//TODO free argv
}
