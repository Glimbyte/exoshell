/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:45:03 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/18 13:46:50 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	quote_removal(t_token *tok)
{
	int		n;
	int		flag;
	char	*tmp_word;

	n = 0;
	flag = 0;
	if (tok->kind == TK_EOF)
		return ;
	while (tok->word[n] != '\0')
	{
		if ((tok->word[n] == '\'' || tok->word[n] == '\"') && flag == 0)
		{
			flag = tok->word[n];
			tmp_word = tok->word;
			tok->word = ft_strextract(n, tok->word);
			free(tmp_word);
		}
		else if (tok->word[n] == flag)
		{
			flag = 0;
			tmp_word = tok->word;
			tok->word = ft_strextract( n, tok->word);
			free(tmp_word);
		}
		else
			n++;
		if (tok->word == NULL)
			fatal_error("cant malloc word <expand.c>");
	}
	quote_removal(tok->next);
}

static int	value_chcker(t_token *tok, const char *s)
{
	int n;
	int	len;

	n = 0;
	len = strlen(s);
	while (tok->word[n] != '\0')
	{
		if (tok->word[n] == '$')
		{
			if (tok->word[n + 1] != '\0' && strncmp(&tok->word[n + 1], s, len) == 0)
				return (1);
		}
		n++;
	}
	return (0);
}

static int	replace_word(t_token *tok, const char *s, char *replace_s)
{
	char	*re_s;
	int		n;
	int		len;

	re_s = calloc(strlen(tok->word) + strlen(replace_s) - strlen(s), sizeof(char));
	n = 0;
	len = 0;
	while (tok->word[n] != '$')
	{
		re_s[n] = tok->word[n];
		len++;
		n++;
	}
	while (*replace_s)
	{
		re_s[n] = *replace_s;
		replace_s++;
		n++;
	}
	len = len + strlen(s) + 2;
	while (tok->word[len] != '\0')
	{
		re_s[n] = tok->word[len];
		len++;
		n++;
	}
	re_s[n] = '\0';
	free(tok->word);
	tok->word = re_s;
	return (1);
}

t_node	*expand(t_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->rhs)
		expand(node->rhs);
	if (node->lhs)
		expand(node->lhs);
	if (node->val)
	{
		quote_removal(node->val);
		while (value_chcker(node->val, "?") != 0)
			replace_word(node->val, "?", "1");
	}
	return (node);
}
