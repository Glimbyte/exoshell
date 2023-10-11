/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:06:17 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 00:23:24 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <limits.h>
#include <bsd/string.h>



void	fatal_error(const char *msg) __attribute__((noreturn));
void	Todo(const char *msg);
