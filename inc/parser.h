/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:40:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/18 13:04:08 by mfujimak         ###   ########.fr       */
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
typedef struct s_node t_node;

typedef struct s_cmd_line t_cmd_line;
struct s_cmd_line
{
	t_token *new_line;
	t_node *sequencial_cmd;
	t_node *delimiter;
};

typedef struct s_delimiter t_del;
struct s_delimiter
{
	t_token *delimiter;
};

typedef struct s_sequencial_cmd t_seq_cmd;
struct s_sequencial_cmd
{
	t_node *piped_commands;
	t_node *delimiter;
	t_node *sequencial_cmd;
};

typedef struct s_piped_commands t_pip_cmd;
struct s_piped_commands
{
	t_node *cmd;
	t_token *pipe;
	t_node *piped_commands;
};

typedef struct s_cmd t_cmd;
struct s_cmd
{
	t_node *arguments;
};

typedef struct s_arguments t_arg;
struct s_arguments
{
	t_node *redirection;
	t_node *string;
	t_node *arguments;
};

typedef struct s_string t_string;
struct s_string
{
	t_token *string;
};

typedef struct s_redirection t_red;
struct s_redirection
{
	t_token *redi;
	t_node *string;
};

typedef struct s_node t_node;
struct s_node
{
	t_node_kind kind;
	t_cmd_line cmd_line;
	t_del del;
	t_seq_cmd seq_cmd;
	t_pip_cmd pip_cmd;
	t_cmd cmd;
	t_arg arg;
	t_string string;
	t_red redirection;
};

t_node *parser(t_token *tok);
void statement(t_node *node, t_token *tok);

bool p_expect(t_token *tok, t_token_kind kind, const char *word);
bool p_accept(t_node *node, t_node_kind kind);
t_node *new_node(t_node_kind kind);

void p_cmd_line(t_node *node, t_token *tok);
void p_delimiter(t_node *node, t_token *tok);
void p_sequential_cmd(t_node *node, t_token *tok);
void p_arguments(t_node *node, t_token *tok);
void p_piped_commands(t_node *node, t_token *tok);
void p_command(t_node *node, t_token *tok);
void p_arguments(t_node *node, t_token *tok);
void p_string(t_node *node, t_token *tok);
void	p_redirection(t_node *node, t_token *tok);
