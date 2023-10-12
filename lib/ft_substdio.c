/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substdio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:52:23 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 23:00:05 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_substdio.h"
#include <string.h>

char *ft_strextract(int extract, char *s)
{
	char	*re_s;
	int		n;
	int		re_n;

	re_s = calloc(1, sizeof(char) * (strlen(s) - 1));
	if (re_s == NULL)
		return (NULL);
	n = 0;
	re_n = 0;
	while (s[n] != '\0')
	{
		if (n == extract)
			n++;
		re_s[re_n] = s[n];
		re_n++;
		n++;
	}
	return (re_s);
}
