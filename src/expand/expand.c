/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:03 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 15:14:44 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "token.h"

t_token *expand(t_token *tok)
{
	quote_removal(tok)
	return (tok);
}

void	quote_removal(t_token *tok)
{
	char	*re_word;
	int		n;

	n = 0;
	if (tok->kind == TK_EOF)
		return ;
	while (tok->word[n] != '\0')

	quote_removal(tok->next);
}
