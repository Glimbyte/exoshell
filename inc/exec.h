/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:03:46 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/25 16:50:45 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_command_exec t_command_exec;
struct s_command_exec
{
	t_redirect	*refirection;
	char		**argv;
	char		*path;
	pid_t		pid;
	int			input_pipe[2];
	int			output_pipe[2];
	t_command_exec	*next;
};

void	exec_scmd(t_node	*node);
void	exec_pipe(t_node	*node, t_command_exec	*cmd_exec);
void	prepare_p_pipe(t_command_exec	*cmd_exec);
void	end_p_pipe(t_command_exec	*cmd_exec);
void	prepare_c_pipe(t_command_exec	*cmd_exec);
void	end_c_pipe(t_command_exec	*cmd_exec);
void	exec_cmd(t_node	*node, t_command_exec	*cmd_exec);
char	**exec_argv(t_node	*node);
char	*exec_arg(t_node	*node);
int		exec_argv_len(t_node	*node);
char	*exec_search_pash(const char *file);
int		exec(t_command_exec	*cmd_exec);

t_redirect	*exec_redirect(t_node	*node);
t_redirect_kind	exec_redirect_kind(t_token *tok);

void	exec_red_show(t_redirect	*redir);
