/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:22:54 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 21:56:49 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redirect	*exec_redirect(t_node	*node)
{
	t_redirect	*redir;

	while (node != NULL && node->lhs->kind != RE_DIRECTUIN)
		node = node->rhs;
	if (node != NULL)
		printf("filename : [ %s ]\n", node->lhs->val->word);
	if (node != NULL && node->lhs->kind ==  RE_DIRECTUIN)
	{
		redir = calloc(1, sizeof(t_redirect));
		redir->filename = strdup(node->lhs->val->word);
		redir->kind = exec_redirect_kind(node->lhs->val);
		redir->fd = atoi(node->lhs->val->word);
		redir->next = exec_redirect(node->rhs);
		return (redir);
	}
	return (NULL);
}

t_redirect_kind	exec_redirect_kind(t_token *tok)
{
	char *redirct[4] = {"<", ">", "<<", ">>"};
	int	n;

	n = 0;
	while(!p_expect(tok, TK_WORD, redirct[n]) && n < 4)
		n++;
	if (n > 3)
		fatal_error("dont redirection <exec_redirection.c>\n");
	if (n == 0)
		return (RK_IN);
	else if (n == 1)
		return (RK_OUT);
	else if (n == 2)
		return (RK_APPEND);
	else if (n == 3)
		return (RK_HEREDOC);
	return (RK_IN);
}

void	exec_red_show(t_redirect	*redir)
{
	if (redir->kind == RK_IN)
		printf("RK_IN\n");
	if (redir->kind == RK_OUT)
		printf("RK_OUT\n");
	if (redir->kind == RK_APPEND)
		printf("RK_APPEND\n");
	if (redir->kind == RK_HEREDOC)
		printf("RK_HEREDOC\n");
	printf ("filename	: %s\n", redir->filename);
	printf ("fd		: %d\n", redir->fd);
	if (redir->next != NULL)
		exec_red_show(redir->next);
}
