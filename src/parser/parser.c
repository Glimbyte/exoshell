/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:35:52 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 18:40:44 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	文脈自由文法　OK　BNF
command_line ::=
      sequencial_commands ";"
    | sequencial_commands

sequencial_commands ::=
      piped_commands ";" sequencial_commands
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
      string

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
t_token	*tok;

t_node	*parser(t_token *token_head)
{
	t_node	*head;

	tok = token_head;
	head = p_cmd_line();
	return (head);
}

t_node	*p_cmd_line()
{
	t_node	*node;

	if (tok->kind == TK_EOF)
		return (new_node(SIMPLE_CMD_LINE, NULL, NULL, NULL));
	node = p_sequential_cmd();
	if (tok->kind != TK_EOF)
	{
		if (p_expect(tok, TK_OP, ";"))
		{
			node = new_node(SIMPLE_CMD_LINE, node, NULL, tok);
			tok = tok->next;
			return(node);
		}
	}
	return(new_node(SIMPLE_CMD_LINE, node, NULL, NULL));
}

t_node	*p_sequential_cmd()
{
	t_node	*node;

	node = p_piped_commands();
	if (tok->kind != TK_EOF)
	{
		if (p_expect(tok, TK_OP, ";") && tok->next->kind != TK_EOF)
		{
			node = new_node(SEQUENTIAL_CMD, node, NULL, tok);
			tok = tok->next;
			node->rhs = p_sequential_cmd();
			return(node);
		}
	}
	return(new_node(SEQUENTIAL_CMD, node, NULL, NULL));
}

t_node	*p_piped_commands()
{
	t_node	*node;

	node = p_command();
	if (tok->kind != TK_EOF)
	{
		if (p_expect(tok, TK_OP, "|"))
		{
			node = new_node(PIPE_CMD, node, NULL, tok);
			tok = tok->next;
			node->rhs = p_piped_commands();
			return(node);
		}
	}
	return(new_node(PIPE_CMD, node, NULL, NULL));
}

t_node	*p_command()
{
	t_node	*node;

	node = p_arguments();
	return (new_node(CMD, node, NULL, NULL));
}

bool	p_is_redirection()
{
	return (strchr( tok->word, '<') || strchr( tok->word, '>'));
}

t_node	*p_arguments()
{
	t_node	*node;

	if (p_is_redirection() &&  tok->next->kind == TK_WORD)
	{
		node = p_redirection();
		if (tok->kind != TK_EOF)
			if (p_is_redirection() || tok->kind == TK_WORD)
				return (new_node(ARGUMENT, node, p_arguments(), NULL));
	}
	else
	{
		node = p_string();
		if (tok->kind != TK_EOF)
			if (p_is_redirection() || tok->kind == TK_WORD)
				return (new_node(ARGUMENT, node, p_arguments(), NULL));
	}
	return (new_node(ARGUMENT, node, NULL, NULL));
}

t_node	*p_string()
{
	t_node	*node;

	if (tok->kind != TK_WORD)
		Todo("Grammary error <Parser error>\n");
	node = new_node(STRING, NULL, NULL, tok);
	tok = tok->next;
	return (node);
}

t_node	*p_redirection()
{
	t_node	*node;

	node = new_node(RE_DIRECTUIN, NULL, NULL, tok);
	tok = tok->next;
	node->rhs = p_string();
	return (node);
}

bool	p_expect(t_token *tok, t_token_kind kind, const char *word)
{
	if (tok->kind == TK_EOF)
		return (FALSE);
	if (kind == tok->kind)
	{
		if(strncmp(tok->word, word, strlen(word)) == 0)
			return (SUCCESS);
	}
	return (FALSE);
}

t_node	*new_node(t_node_kind kind, t_node *lhs, t_node *rhs, t_token *val)
{
	t_node *new_node;

	new_node = calloc(1,sizeof(t_node));
	if (new_node == NULL)
		fatal_error("cant calloc <paeser.c>");
	new_node->kind = kind;
	new_node->lhs = lhs;
	new_node->rhs = rhs;
	new_node->val = val;
	return (new_node);
}


void	parser_check(char *filename, t_node *node)
{
	FILE *outputfile;

	outputfile = fopen(filename, "w");
	if (outputfile == NULL) {
		printf("cannot open\n");
	exit(1);
	}

	fprintf(outputfile, "digraph PARSER {\n");
	node_check(outputfile ,node);
	fprintf(outputfile, "}\n");
	fclose(outputfile);
}

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

void	node_check(FILE *outputfile ,t_node *node)
{
	if (node->kind == SIMPLE_CMD_LINE)
		fprintf(outputfile, "	NODE_%p [label=\"%s\\n\"];\n", node, "SIMPLE_CMD_LINE");
	else if (node->kind == RE_DIRECTUIN)
		fprintf(outputfile, "	NODE_%p [label=\"%s [ %s ]\\n\"];\n", node, "RE_DIRECTUIN", node->val->word);
	else if (node->kind == SEQUENTIAL_CMD)
		fprintf(outputfile, "	NODE_%p [label=\"%s\\n\"];\n", node, "SEQUENTIAL_CMD");
	else if (node->kind == PIPE_CMD)
		fprintf(outputfile, "	NODE_%p [label=\"%s\\n\"];\n", node, "PIPE_CMD");
	else if (node->kind == CMD)
		fprintf(outputfile, "	NODE_%p [label=\"%s\\n\"];\n", node, "CMD");
	else if (node->kind == ARGUMENT)
		fprintf(outputfile, "	NODE_%p [label=\"%s\\n\"];\n", node, "ARGUMENT");
	else if (node->kind == STRING)
		fprintf(outputfile, "	NODE_%p [label=\"%s < %s >\\n\"];\n", node, "STRING", node->val->word);
	if (node->lhs != NULL)
		fprintf(outputfile, "	NODE_%p -> NODE_%p\n", node, node->lhs);
	if (node->rhs != NULL)
		fprintf(outputfile, "	NODE_%p -> NODE_%p\n", node, node->rhs);
	if (node->lhs != NULL)
		node_check(outputfile , node->lhs);
	if (node->rhs != NULL)
		node_check(outputfile , node->rhs);
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
