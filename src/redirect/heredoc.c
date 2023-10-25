/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:20:17 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/25 16:00:46 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *heredoc(t_command_exec	*cmd_exec)
{
	(void)cmd_exec;
	return (strdup("i dont make heredoc\n"));
}
