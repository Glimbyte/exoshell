/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:24:41 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/12 13:12:47 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdlib.h>


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

t_token	*tokenize(char *line);
bool	is_blank(char s);
bool	is_metacharacter(char s);
bool	is_word(char s);
int		is_control_op(char *line);
bool	is_single_quote(char s);
int		word(t_token *cur, char *line);
int		control_op(int op_len, t_token *cur, char *line);
t_token	*new_token(t_token_kind kind,t_token *cur, char *word);
int		single_quote(char *line);
int		duble_quote(char *line);
bool	is_duble_quote(char s);
