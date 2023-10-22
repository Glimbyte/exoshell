/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:40:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 13:05:42 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

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

typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
	t_node		*rhs;
	t_node		*lhs;
	t_token		*val;
};

t_node *parser(t_token *tok);
void	statement(t_node *node, t_token **tok);

bool	p_expect(t_token *tok, t_token_kind kind, const char *word);
bool	p_accept(t_node *node, t_node_kind kind);
t_node	*new_node(t_node_kind kind, t_node *rhs, t_node *lhs, t_token *val);

t_node	*p_cmd_line();
t_node	*p_sequential_cmd();
t_node	*p_arguments();
t_node	*p_piped_commands();
t_node	*p_command();
t_node	*p_arguments();
t_node	*p_string();
t_node	*p_redirection();

void	parser_check(char *filename, t_node *node);
void	node_check(FILE *outputfile ,t_node *node);
