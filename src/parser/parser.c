/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:35:52 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/12 13:38:30 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
enum e_node_kind
{
	ND_SIMPLE_CMD,
};
typedef enum e_node_kind t_node_kind;

typedef struct s_node t_node;
struct s_node
{
	t_node_kind kind;
	t_node *next;
	t_token *args;
};

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
} t_token_kind;

typedef struct s_token t_token;

struct s_token
{
	char *word;
	t_token_kind kind;
	t_token *next;
};
*/

#include "shell.h"

t_node *parser(t_token *tok)
{
	t_node	head;
	t_node	*cur;
	t_token	args;

	new_node( ND_SIMPLE_CMD, &head, NULL);
	if (head.next == NULL)
		fatal_error("cant calloc <parser.c>");
	cur = head.next;
	args.next = NULL;
	while (tok->kind != TK_EOF)
	{
		if (tok->kind == TK_WORD)
			add_token(TK_WORD, &args, tok->word);
		else
			Todo("make parser");
		tok = tok->next;
	}
	add_token(TK_EOF, &args, NULL);
	cur->args = args.next;
	return (head.next);
}

void	add_token(t_token_kind kind,t_token *tok, char *word)
{
	if (tok->next == NULL)
	{
		new_token(kind, tok, word);
		return ;
	}
	add_token(kind,tok->next, word);
}


t_node *new_node(t_node_kind kind, t_node *cur, t_token *args)
{
	t_node *new_node;
	new_node = calloc(1, sizeof(t_node));
	if (new_node == NULL)
		fatal_error("cant calloc <parser.c>");
	cur->next = new_node;
	new_node->args =args;
	new_node->kind =kind;
	return (new_node);
}
