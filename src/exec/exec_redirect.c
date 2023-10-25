/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:22:54 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/25 16:01:34 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redirect	*exec_redirect(t_node	*node, t_command_exec	*cmd_exec)
{
	t_redirect	*redir;

	while (node != NULL && node->lhs->kind != RE_DIRECTUIN)
		node = node->rhs;
	if (node != NULL  && node->lhs->kind == RE_DIRECTUIN)
		printf("filename : [ %s ]\n", node->lhs->val->next->word);
	if (node != NULL && node->lhs->kind ==  RE_DIRECTUIN)
	{
		redir = calloc(1, sizeof(t_redirect));
		redir->kind = exec_redirect_kind(node->lhs->val);
		if (redir->kind != RK_HEREDOC)
			redir->filename = strdup(node->lhs->val->next->word);
		else
			redir->filename = heredoc(cmd_exec);
		redir->fd = atoi(node->lhs->val->word);
		redir->next = exec_redirect(node->rhs, cmd_exec);
		return (redir);
	}
	return (NULL);
}

t_redirect_kind	exec_redirect_kind(t_token *tok)
{
	if (p_expect(tok, TK_WORD, ">>"))
		return (RK_APPEND);
	else if (p_expect(tok, TK_WORD, "<<"))
		return (RK_HEREDOC);
	else if (p_expect(tok, TK_WORD, "<"))
		return (RK_IN);
	else if (p_expect(tok, TK_WORD, ">"))
		return (RK_OUT);
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
