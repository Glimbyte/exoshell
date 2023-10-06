/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:23:12 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/06 11:41:53 by mfujimak         ###   ########.fr       */
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

t_token	*tokenize(char *command)
{
	t_token head;
	t_token *cur;

	head.next = NULL;
	cur = &head;
	while (*command)
	{
		while (is_blank(*command))
			command++;
		is_control_op(command, {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"}, 9);
		command++;
	}
	return (head.next);
}

bool	is_blank(char s)
{
	return (s && strchr(" \t"));
}

bool	is_metacharacter(char s)
{
	return (s && strchr("|&;()<> \t" , s));
}

bool	is_word(char s)
{
	return (s && !is_metacharacter(s));
}

int		is_control_op(char *command, char *con_op[], int len)
{
	int	f_n;
	int s_n;
	int	flag;

	flag = 0;
	f_n = 0;
	while (f_n < len)
	{
		s_n = 0;
		while (con_op[f_n][s_n])
		{
			flag = 1;
			if (command[s_n] != con_op[f_n][s_n])
			{
				flag = 0;
				break;
			}
			s_n++;
		}
		if (flag == 1)
			break;
		f_n++;
	}
	if (flag == 1)
	{
		return (strlen(con_op[f_n]));
	}
	return (0);
}

t_token	*new_token(t_token_kind kind,t_token *cur, char *word)
{
	t_token *new_token;

	new_token = calloc(sizeof(t_token));
	if (new_token == NULL)
		fatal_error("can not make new_token <token.c>");
	cur->next = new_token;
	new_token->next = new_token;
	new_token->word = word;
	new_token->kind = kind;
	return (new_token);
}




