/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:23:12 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 11:50:21 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
DEFINITIONS
       The following definitions are used throughout the rest of this document.
       blank  A space or tab.
       word   A sequence of characters considered as a single unit by the shell.  Also known as a token.
       name   A word consisting only of alphanumeric characters and underscores, and beginning with an alphabetic  character  or
              an underscore.  Also referred to as an identifier.
       metacharacter
              A character that, when unquoted, separates words.  One of the following:
              |  & ; ( ) < > space tab newline
       control operator
              A token that performs a control function.  It is one of the following symbols:
              || & && ; ;; ;& ;;& ( ) | |& <newline>

定義
	このドキュメントの残りの部分では、 以下の定義を使用します。

	ブランク (blank)
	空白文字またはタブ文字
	単語 (word)
	シェルが 1 単位とみなす文字の並び。 トークン (token) とも言われます。
	名前 (name)
	英数字とアンダースコア文字だけから構成され、 かつ最初の文字が英字かアンダースコア文字である 単語。 識別子 (identifier) とも言われます。
	メタ文字 (metacharacter)
	クォートされていない場合に、単語区切りとなる文字。 以下の文字のうちのいずれかです:
	| & ; ( ) < > space tab

	制御演算子 (control operator)
	制御機能を持つ トークン。 以下のシンボルのうちのいずれかです:
	|| & && ; ;; ( ) | |& <newline>

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
} t_token_kind;
*/

#include "shell.h"

int	syntax_error;

t_token	*tokenize(const char *line)
{
	t_token head;
	t_token *cur;
	int		op_len;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		while (is_blank(*line))
			line++;
		op_len = is_control_op(line);
		if (op_len)
			line += control_op(op_len, cur, line);
		else if (is_word(*line))
			line += word(cur, line);
		cur = cur->next;
		if (tokenize_error(head.next))
			return (NULL);
	}
	new_token( TK_EOF, cur, NULL);
	return (head.next);
}

int	word(t_token *cur, const char *line)
{
	int		word_len;
	char	*word;

	word_len = 0;
	while (is_word(line[word_len]) && !is_redirection(line[word_len]))
	{
		if(is_single_quote(line[word_len]))
			word_len += single_quote(line + word_len);
		else if(is_duble_quote(line[word_len]))
			word_len += duble_quote(line + word_len);
		else
			word_len++;
	}
	while (is_redirection(line[word_len]))
		word_len++;
	word = strndup(line, word_len);
	if (word == NULL)
		fatal_error("can not make word <token.c>");
	new_token(TK_WORD, cur, word);
	return(word_len);
}

int	single_quote(const char *line)
{
	int	len;

	len = 1;
	while(!is_single_quote(line[len]) && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		syntax_error = 1;
	return (len + 1);
}

int	duble_quote(const char *line)
{
	int	len;

	len = 1;
	while(!is_duble_quote(line[len]) && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		syntax_error = 2;
	return (len + 1);
}

// int	redirection(t_token *cur, const char *line)
// {
// 	int		word_len;
// 	char	*word;

// 	word_len = 0;
// 	while (is_redirection(line[word_len]))
// 		word_len++;
// 	word = strndup(line, word_len);
// 	if (word == NULL)
// 		fatal_error("can not make word <token.c>");
// 	new_token(TK_WORD, cur, word);
// 	return(word_len);
// }

int	control_op(const int op_len, t_token *cur, const char *line)
{
	char	*op_word;

	op_word = strndup(line, op_len);
	if (op_word == NULL)
		fatal_error("can not make op_word <token.c>");
	new_token( TK_OP, cur, op_word);
	return (op_len);
}

t_token	*new_token(t_token_kind kind,t_token *cur, char *word)
{
	t_token *new_token;

	new_token = calloc( 1, sizeof(t_token));
	if (new_token == NULL)
		fatal_error("can not make new_token <token.c>");
	cur->next = new_token;
	new_token->next = NULL;
	new_token->word = word;
	new_token->kind = kind;
	return (new_token);
}

bool	is_blank(const char s)
{
	return (s && strchr(" \t", s));
}

bool	is_metacharacter(const char s)
{
	return (s && strchr("|&;() \t" , s));
}

bool	is_redirection(const char s)
{
	return (s && strchr("<>" , s));
}

bool	is_word(const char s)
{
	return (s && !is_metacharacter(s));
}

bool	is_single_quote(const char s)
{
	return (s == '\'');
}

bool	is_duble_quote(const char s)
{
	return (s == '\"');
}

int	is_control_op(const char *line)
{
	long unsigned int	n;
	char *con_op[] = {"||", "&&", ";;", "|", "&", ";", "(", ")", "\n"};

	n = 0;
	while (n < sizeof(con_op) / sizeof(*con_op))
	{
		if (strncmp(line, con_op[n], strlen(con_op[n])) == 0)
			return (strlen(con_op[n]));
		n++;
	}
	return (false);
}

int	tokenize_error(t_token *head)
{
	if (syntax_error == 0)
		return (FALSE);
	else if (syntax_error == 1)
		printf("dont have single_quote <Tokenize Error>\n");
	else if (syntax_error == 2)
		printf("dont have duble_quote. <Tokenize Error>\n");
	if (syntax_error)
	{
		token_free(head);
		return (SUCCESS);
	}
	return (FALSE);
}
void	token_free(t_token *head)
{
	if (head->next != NULL)
		token_free(head->next);
	if (head->word)
		free(head->word);
	free(head);
}

void	token_check(const t_token *tok)
{
	int	n;

	n = 0;
	while (1)
	{
		if (tok->kind == TK_WORD)
			printf("[%d]	type TK_WORD	[%s]\n", n, tok->word);
		else if (tok->kind == TK_OP)
			printf("[%d]	type TK_OP	[%s]\n", n, tok->word);
		else if (tok->kind == TK_EOF)
		{
			printf("[%d]	type TK_EOF	[%s]\n", n, tok->word);
			break;
		}
		n++;
		tok = tok->next;
	}
}
