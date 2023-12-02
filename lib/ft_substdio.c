/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substdio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:52:23 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/02 14:17:08 by mfujimak         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	n;

	if (s1 == 0 || s2 == 0)
		return (0);
	s = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (s == 0)
		return (0);
	n = 0;
	while (strlen(s1) > n)
	{
		s[n] = s1[n];
		n++;
	}
	n = 0;
	while (strlen(s2) > n)
	{
		s[strlen(s1) + n] = s2[n];
		n++;
	}
	s[strlen(s1) + strlen(s2)] = 0;
	return (s);
}

