/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:35:52 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/18 13:21:45 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	文脈自由文法　OK　BNF
command_line ::=
      "\n"
    | sequencial_commands delimiter "\n"
    | sequencial_commands "\n"

delimiter ::=
      ";"

sequencial_commands ::=
      piped_commands delimiter sequencial_commands
    | piped_commands

piped_commands ::=
      command "|" piped_commands
    | command

command ::=
      arguments

arguments ::=
      redirection
    | redirection arguments
    | string
    | string arguments

string ::=
      expandable <no_space> string
    | expandable
    | not_expandable <no_space> string
    | not_expandable
    | expandable_quoted <no_space> string
    | expandable_quoted

redirection ::=
      "<" string
    | ">" string
    | ">>" string
    | "<<" string
*/

/*
typedef enum e_node_kind t_node_kind;
enum e_node_kind
{
	SIMPLE_CMD_LINE,
	RE_DIRECTUIN,
	DELIMITER,
	SEQUENTIAL_CMD,
	PIPE_CMD,
	CMD,
	ARGUMENT,
	STRING,
};

*/

#include "shell.h"

t_node	*parser(t_token *tok)
{
	printf("parser\n");
	t_node	*head;

	head = new_node(SIMPLE_CMD_LINE);
	statement(head, tok);
	return (head);
}

void	statement(t_node *node, t_token *tok)
{
	printf("statement\n");
	if (p_accept(node, SIMPLE_CMD_LINE))
		p_cmd_line( node, tok);
	else if (p_accept(node, DELIMITER))
		p_delimiter( node, tok);
	else if (p_accept(node, SEQUENTIAL_CMD))
		p_sequential_cmd(node, tok);
	else if (p_accept(node, PIPE_CMD))
		p_piped_commands( node, tok);
	else if (p_accept(node, CMD))
		p_command( node, tok);
	else if (p_accept(node, ARGUMENT))
		p_arguments( node, tok);
	else if (p_accept(node, STRING))
		p_string( node, tok);
	else if (p_accept(node, RE_DIRECTUIN))
		p_redirection( node, tok);
}

void	p_cmd_line(t_node *node, t_token *tok)
{
	printf("cmd_line\n");
	t_token	*tmp_tok;

	tmp_tok = tok;
	while (!(p_expect(tmp_tok, TK_OP, ";")))
		tmp_tok = tmp_tok->next;
		///???
	if (p_expect(tmp_tok->next, TK_OP, ";"))
	{
		node->cmd_line.sequencial_cmd = new_node(SEQUENTIAL_CMD);
		node->cmd_line.delimiter = new_node(DELIMITER);
		statement(node->cmd_line.delimiter, tmp_tok->next);
		new_token(TK_EOF, tmp_tok, NULL);
		statement(node->cmd_line.sequencial_cmd, tok);
	}
	else
	{
		node->cmd_line.sequencial_cmd = new_node(SEQUENTIAL_CMD);
		node->cmd_line.delimiter = NULL;
		statement(node->cmd_line.sequencial_cmd, tok);
	}
}

void	p_delimiter(t_node *node, t_token *tok)
{
	printf("delimiter\n");
	if (p_expect(tok, TK_OP, ";"))
		node->del.delimiter = tok;
	else
		Todo("cant del");
}

void	p_sequential_cmd(t_node *node, t_token *tok)
{
	printf("seq_cmd\n");
	t_token	*tmp_tok;

	tmp_tok = tok;
	while (!p_expect(tmp_tok->next, TK_OP, ";") && tmp_tok->next->kind != TK_EOF)
		tmp_tok = tmp_tok->next;
	if (tmp_tok->next->kind == TK_EOF)
	{
		node->seq_cmd.sequencial_cmd = NULL;
		node->seq_cmd.delimiter = NULL;
		node->seq_cmd.piped_commands = new_node(PIPE_CMD);
		statement(node->seq_cmd.piped_commands, tok);
	}
	else
	{
		node->seq_cmd.piped_commands = new_node(PIPE_CMD);
		node->seq_cmd.delimiter = new_node(DELIMITER);
		node->seq_cmd.sequencial_cmd = new_node(SEQUENTIAL_CMD);
		statement(node->seq_cmd.sequencial_cmd, tmp_tok->next->next);
		new_token(TK_EOF, tmp_tok->next, NULL);
		statement(node->seq_cmd.delimiter, tmp_tok->next);
		new_token(TK_EOF, tmp_tok, NULL);
		statement(node->seq_cmd.piped_commands, tok);
	}
}

void	p_piped_commands(t_node *node, t_token *tok)
{
	printf("pip_cmd\n");
	t_token	*tmp_tok;

	tmp_tok = tok;
	while (!p_expect(tmp_tok->next, TK_OP, "|") && tmp_tok->next->kind != TK_EOF)
		tmp_tok = tmp_tok->next;
	if (tmp_tok->next->kind == TK_EOF)
	{
		node->pip_cmd.cmd = new_node(CMD);
		node->pip_cmd.piped_commands = NULL;
		node->pip_cmd.pipe = NULL;
		statement(node->pip_cmd.cmd, tok);
	}
	else
	{
		node->pip_cmd.cmd = new_node(CMD);
		node->pip_cmd.piped_commands = new_node(PIPE_CMD);
		node->pip_cmd.pipe = tmp_tok->next;
		statement(node->pip_cmd.cmd, tmp_tok->next->next);
		new_token(TK_EOF, tmp_tok->next, NULL);
		new_token(TK_EOF, tmp_tok, NULL);
		statement(node->pip_cmd.cmd, tok);
	}
}

void	p_command(t_node *node, t_token *tok)
{
	printf("cmd\n");
	node->cmd.arguments = new_node(ARGUMENT);
	statement(node->cmd.arguments, tok);
}

void	p_arguments(t_node *node, t_token *tok)
{
	printf("arg_cmd\n");
	if ((strchr( tok->word, '<') || strchr( tok->word, '>')) && tok->kind == TK_OP)
	{
		if (tok->next->kind != TK_WORD)
			Todo("redirection dont have word");
		else if (tok->next->kind == TK_WORD && tok->next->next->kind == TK_WORD)
		{
			node->arg.redirection = new_node(RE_DIRECTUIN);
			node->arg.arguments = new_node(ARGUMENT);
			statement(node->arg.arguments, tok->next->next);
			new_token(TK_EOF ,tok->next, NULL);
			statement(node->arg.redirection, tok);
		}
		else if (tok->next->kind == TK_WORD)
		{
			node->arg.arguments = NULL;
			node->arg.redirection = new_node(RE_DIRECTUIN);
			statement(node->arg.redirection, tok);
		}
	}
	else
	{
		if (tok->kind != TK_WORD)
			Todo("redirection dont have word mistake!!");
		else if (tok->next->kind  == TK_WORD)
		{
			node->arg.redirection = NULL;
			node->arg.string = new_node(STRING);
			node->arg.arguments = new_node(ARGUMENT);
			statement(node->arg.arguments, tok->next);
			new_token(TK_EOF, tok, NULL);
			statement(node->arg.string, tok);
		}
		else if (tok->kind == TK_WORD)
		{
			node->arg.redirection = NULL;
			node->arg.arguments = NULL;
			node->arg.string = new_node(STRING);
			statement(node->arg.string, tok);
		}
	}
}

void	p_string(t_node *node, t_token *tok)
{
	printf("string\n");
	node->string.string = tok;
}

void	p_redirection(t_node *node, t_token *tok)
{
	printf("redirection\n");
	node->redirection.redi = tok;
	node->redirection.string = new_node(STRING);
	statement(node->redirection.string, tok->next);
	new_token(TK_EOF, tok, NULL);
}

bool	p_expect(t_token *tok, t_token_kind kind, const char *word)
{
	if (tok->kind == TK_EOF)
		return (FALSE);
	if (kind == tok->kind)
		if(strncmp(tok->word, word, strlen(word)) == 0)
			return (SUCCESS);
	return (FALSE);
}

bool	p_accept(t_node *node, t_node_kind kind)
{
	return (kind == node->kind);
}

t_node	*new_node(t_node_kind kind)
{
	t_node *new_node;
	new_node = calloc(1, sizeof(t_node*));
	if (new_node == NULL)
		fatal_error("cant calloc <paeser.c>");
	new_node->kind = kind;
	return (new_node);
}


// t_node *parser(t_token *tok)
// {
// 	t_node	head;
// 	t_node	*cur;
// 	t_token	args;

// 	new_node(SIMPLE_CMD, &head, NULL);
// 	if (head.next == NULL)
// 		fatal_error("cant calloc <parser.c>");
// 	cur = head.next;
// 	args.next = NULL;
// 	while (tok->kind != TK_EOF)
// 	{
// 		if (tok->kind == TK_WORD)
// 			add_token(TK_WORD, &args, tok->word);
// 		else
// 			Todo("make parser");
// 		tok = tok->next;
// 	}
// 	add_token(TK_EOF, &args, NULL);
// 	cur->args = args.next;
// 	return (head.next);
// }

// void	add_token(t_token_kind kind,t_token *tok, char *word)
// {
// 	if (tok->next == NULL)
// 	{
// 		new_token(kind, tok, word);
// 		return ;
// 	}
// 	add_token(kind,tok->next, word);
// }


// t_node *new_node(t_node_kind kind, t_node *cur, t_token *args)
// {
// 	t_node *new_node;
// 	new_node = calloc(1, sizeof(t_node));
// 	if (new_node == NULL)
// 		fatal_error("cant calloc <parser.c>");
// 	cur->next = new_node;
// 	new_node->args =args;
// 	new_node->kind =kind;
// 	return (new_node);
// }
