/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:53:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/26 15:00:20 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_cmd(t_node	*node, t_command_exec	*cmd_exec)
{
	if (node->kind != CMD)
		fatal_error("not CMD <exec_cmd.c>\n");

	cmd_exec->argv = exec_argv(node);
	cmd_exec->refirection = exec_redirect(node->lhs);
	if (cmd_exec->refirection != NULL)
		exec_red_show(cmd_exec->refirection);
	if(strchr(cmd_exec->argv[0], '/'))
		cmd_exec->path = strdup(cmd_exec->argv[0]);
	else
		cmd_exec->path = exec_search_pash(cmd_exec->argv[0]);
	if (cmd_exec->path != NULL)
		exec(cmd_exec);
}

char	**exec_argv(t_node	*node)
{
	if (node->kind != CMD)
		fatal_error("not CMD <exec_cmd.c>\n");
	char	**argv;

	argv = calloc(3, sizeof(char*));
	if (argv == NULL)
		fatal_error("cant calloc <exec_cmd.c>\n");
	node = node->lhs;
	argv[0] = strdup(node->lhs->val->word);
	argv[1] = exec_arg(node->rhs);
	argv[2] = NULL;
	return (argv);
}

char	*exec_arg(t_node	*node)
{
	char	*argv;
	char	*arg;
	int		n;

	if (node == NULL || node->lhs->kind == RE_DIRECTUIN)
		return (NULL);
	argv = calloc(1, exec_argv_len(node) * sizeof(char));
	arg = argv;
	while (1)
	{
		n = 0;
		while (node->lhs->val->word[n] != '\0')
		{
			*arg = node->lhs->val->word[n];
			n++;
			arg++;
		}
		if (node->rhs == NULL || node->rhs->lhs->kind == RE_DIRECTUIN)
			break ;
		*arg = ' ';
		node = node->rhs;
		arg++;
	}
	return (argv);
}

int		exec_argv_len(t_node	*node)
{
	if (node->kind != ARGUMENT)
		fatal_error("not ARGUMENT <exec_cmd.c>\n");
	int	len;

	len = 0;
	len += strlen(node->lhs->val->word);
	while (node->rhs != NULL && node->rhs->kind != RE_DIRECTUIN)
	{
		len++;
		len += strlen(node->lhs->val->word);
		node = node->rhs;
	}
	return (len);
}

char	*exec_search_pash(const char *file)
{
	int		n;
	char	*path;
	char	*end_p;
	char	tmp_value[PATH_MAX];
	char	*re;

	path = getenv("PATH");
	if (path == NULL)
		fatal_error("can not get env");
	bzero(tmp_value,PATH_MAX);
	end_p = strchr(path, ':');
	while (end_p != NULL)
	{
		n = 0;
		while(end_p != path)
			tmp_value[n++] = *path++;
		strlcat(tmp_value, "/", PATH_MAX);
		strlcat(tmp_value, file, PATH_MAX);
		if (access(tmp_value, X_OK) == 0)
		{
			re = strdup(tmp_value);
			return (re);
		}
		bzero(tmp_value,PATH_MAX);
		path++;
		end_p = strchr(path, ':');
	}
	printf("cant find path <exec_pipe.c>\n");
	return (NULL);
}
