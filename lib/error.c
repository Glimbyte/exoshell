/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:05:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 00:23:13 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	fatal_error(const char *msg)
{
	dprintf(1, "Fatal Error: %s\n", msg);
	exit(1);
}

void	Todo(const char *msg)
{
	dprintf(1, "TODO: %s\n", msg);
	exit(1);
}
