/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:03:09 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/13 03:27:09 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*exec_token(t_token *tok)
{
	char	*argv;
	char	*re_argv;
	int		n;
	argv = calloc( 1, sizeof(char) * token_len(tok));
	if (argv == NULL)
		fatal_error("cant calloc or token <exe_token.c>");
	re_argv = argv;
	while (tok->kind == TK_WORD)
	{
		n = 0;
		while (tok->word[n] != '\0')
		{
			*argv = tok->word[n];
			n++;
			argv++;
		}
		*argv = ' ';
		argv++;
		tok = tok->next;
	}
	return (re_argv);
}

int	token_len(t_token *tok)
{
	int n;

	n = 0;
	while (tok->kind == TK_WORD)
	{
		n += strlen(tok->word);
		n++;
		tok = tok->next;
	}
	n--;
	return (n);
}


// char	**exec_token(t_token *tok)
// {
// 	char	**argv;
// 	char	*str;
// 	int		n;

// 	argv = calloc( 1, sizeof(char *) * token_len(tok));
// 	if (argv == NULL)
// 		fatal_error("cant calloc or token dont have word <exe_token.c>");
// 	n = 0;
// 	while (tok->kind == TK_WORD)
// 	{
// 		str = strdup(tok->word);
// 		if (str == NULL)
// 			fatal_error("cant calloc <exe_token.c>");
// 		argv[n] = str;
// 		n++;
// 		tok = tok->next;
// 	}
// 	return (argv);
// }

// int	token_len(t_token *tok)
// {
// 	int	n;

// 	n = 0;
// 	while (tok->kind == TK_WORD)
// 	{
// 		tok = tok->next;
// 		n++;
// 	}
// 	return (n);
// }
