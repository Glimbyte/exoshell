/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:24:41 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/10 10:17:18 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "ft_subbool.h"

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

t_token	*tokenize(char *command);
bool	is_blank(char s);
bool	is_metacharacter(char s);
bool	is_word(char s);
int	is_control_op(char *command);
int	word(t_token *cur, char *command);
int	control_op(int op_len, t_token *cur, char *command);
t_token	*new_token(t_token_kind kind,t_token *cur, char *word);
