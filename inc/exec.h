/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:03:46 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/06 11:19:02 by mfujimak         ###   ########.fr       */
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

void	fatal_error(const char *msg) __attribute__((noreturn));
int		exec(char *path);
char	*exec_search_pash(const char *file);
