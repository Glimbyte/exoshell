/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:03:46 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/13 03:20:36 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <limits.h>
#include <bsd/string.h>

int		exec(char *path, char **argv);
char	*exec_search_pash(const char *file);
void	exec_path(char *path, char **argv);
char	*exec_token(t_token *tok);
int		token_len(t_token *tok);
void	exec_cmd(char *path, t_token *tok);
