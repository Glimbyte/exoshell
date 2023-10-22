/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:03:46 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 21:29:55 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_command_exec t_command_exec;
struct s_command_exec
{
	t_redirect	*refirection;
	char	**argv;
	pid_t		pid;
};

void	exec_cmd(t_node	*node);
void	exec_pipe(t_node	*node);
char	**exec_argv(t_node	*node);
char	*exec_arg(t_node	*node);
int		exec_argv_len(t_node	*node);
char	*exec_search_pash(const char *file);
int		exec(char *path, char **argv);

t_redirect	*exec_redirect(t_node	*node);
t_redirect_kind	exec_redirect_kind(t_token *tok);


void	exec_red_show(t_redirect	*redir);
