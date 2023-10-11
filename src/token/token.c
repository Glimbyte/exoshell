/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:23:12 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/11 14:39:38 by mfujimak         ###   ########.fr       */
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

#include "token.h"
#include "error.h"

t_token	*tokenize(char *line)
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
		else if (is_single_quote(*line))
			line += single_quote(cur, line);
		else if (is_word(*line))
			line += word(cur, line);
		cur = cur->next;
	}
	new_token( TK_EOF, cur, NULL);
	return (head.next);
}

bool	is_blank(char s)
{
	return (s && strchr(" \t", s));
}

bool	is_metacharacter(char s)
{
	return (s && strchr("|&;()<> \t" , s));
}

bool	is_word(char s)
{
	return (s && !is_metacharacter(s));
}

bool	is_single_quote(char s)
{
	return (s == '\'');
}

int	is_control_op(char *line)
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

int	word(t_token *cur, char *line)
{
	int	word_len;
	char	*word;

	word_len = 0;
	while (is_word(line[word_len]))
		word_len++;
	word = strndup(line, word_len);
	if (word == NULL)
		fatal_error("can not make word <token.c>");
	new_token(TK_WORD, cur, word);
	return(word_len);
}

int	control_op(int op_len, t_token *cur, char *line)
{
	char	*op_word;

	op_word = strndup(line, op_len);
	if (op_word == NULL)
		fatal_error("can not make op_word <token.c>");
	new_token( TK_OP, cur, op_word);
	return (op_len);
}

int	single_quote(t_token *cur, char *line)
{
	int	len;
	char	*word;

	len = 1;
	while(!is_single_quote(line[len]) && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		Todo("dont have single_quote");
	if (len != 0)
	{
		word = strndup(line, len + 1);
		if (word == NULL)
			fatal_error("can not make op_word <token.c>");
		new_token( TK_WORD, cur, word);
	} else
		cur->next = cur;
	return (len + 1);
}

t_token	*new_token(t_token_kind kind,t_token *cur, char *word)
{
	t_token *new_token;

	new_token = calloc( 1, sizeof(t_token));
	if (new_token == NULL)
		fatal_error("can not make new_token <token.c>");
	cur->next = new_token;
	new_token->next = new_token;
	new_token->word = word;
	new_token->kind = kind;
	return (new_token);
}




