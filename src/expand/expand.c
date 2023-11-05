/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:03 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/03 21:20:14 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token *expand(t_node *node)
{
	(void)node;
	return (NULL);
}

void	quote_removal(t_token *tok)
{
	int		n;
	int		flag;

	n = 0;
	flag = 0;
	if (tok->kind == TK_EOF)
		return ;
	while (tok->word[n] != '\0')
	{
		if ((tok->word[n] == '\'' || tok->word[n] == '\"') && flag == 0)
		{
			flag = tok->word[n];
			tok->word = ft_strextract( n, tok->word);
		}
		else if (tok->word[n] == flag)
		{
			flag = 0;
			tok->word = ft_strextract( n, tok->word);
		}
		else
			n++;
		if (tok->word == NULL)
			fatal_error("cant malloc word <expand.c>");
	}
	quote_removal(tok->next);
}
