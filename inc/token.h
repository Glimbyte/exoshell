/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:24:41 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/20 12:56:50 by mfujimak         ###   ########.fr       */
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

t_token	*tokenize(const char *line);

int		word(t_token *cur, const char *line);
int		single_quote(const char *line);
int		duble_quote(const char *line);
int		control_op(const int op_len, t_token *cur, const char *line);
t_token	*new_token(t_token_kind kind,t_token *cur, char *word);
bool	is_blank(const char s);
bool	is_metacharacter(const char s);
bool	is_redirection(const char s);
bool	is_word(const char s);
bool	is_single_quote(const char s);
bool	is_duble_quote(const char s);
int		is_control_op(const char *line);
int		redirection(t_token *cur, const char *line);

int		tokenize_error(t_token *head);
void	token_free(t_token *head);

void	token_check(const t_token *tok);
