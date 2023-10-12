/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:40:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/12 13:20:19 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

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

t_node *new_node(t_node_kind kind, t_node *cur, t_token *args);
t_node *parser(t_token *tok);
void	add_token( t_token_kind kind, t_token *tok, char *word);
