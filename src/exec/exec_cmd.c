/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:53:20 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/06 19:24:32 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exec_cmd(t_node	*node, t_command_exec	*cmd_exec)
{
	if (node->kind != CMD)
		fatal_error("not CMD <exec_cmd.c>\n");

	cmd_exec->argv = exec_arg(node);
	cmd_exec->refirection = exec_redirect(node->lhs);
	if (cmd_exec->refirection != NULL)
		exec_red_show(cmd_exec->refirection);
	if (buildin_checker(cmd_exec->argv[0]))
		buildin_cmd(cmd_exec);
	else
	{
		if(strchr(cmd_exec->argv[0], '/'))
			cmd_exec->path = strdup(cmd_exec->argv[0]);
		else
			cmd_exec->path = exec_search_pash(cmd_exec->argv[0], cmd_exec->map);
		if (cmd_exec->path != NULL)
			exec(cmd_exec);
		else
			printf("cant find path <exec_pipe.c>\n");
	}
}

char	**exec_argv(t_node	*node)
{
	if (node->kind != CMD)
		fatal_error("not CMD <exec_cmd.c>\n");
	char	**argv;

	argv = calloc(3, sizeof(char*));
	if (argv == NULL)
		fatal_error("cant calloc <exec_cmd.c>\n");
	argv[0] = strdup(node->lhs->val->word);
	//argv[1] = exec_arg(node->rhs);
	argv[2] = NULL;
	return (argv);
}

char	**exec_arg(t_node	*node)
{
	char	**argv;
	int		n;

	if (node->kind != CMD)
		fatal_error("not CMD <exec_cmd.c>\n");
	node = node->lhs;
	if (node == NULL || node->lhs->kind == RE_DIRECTUIN)
		return (NULL);
	argv = calloc(exec_argv_len(node) + 1, sizeof(char *));
	n = 0;
	while (1)
	{
		argv[n] = strdup(node->lhs->val->word);
		n++;
		if (node->rhs == NULL || node->rhs->lhs->kind == RE_DIRECTUIN)
			break ;
		node = node->rhs;
	}
	argv[n] = NULL;
	return (argv);
}

int		exec_argv_len(t_node	*node)
{
	int len;

	len = 1;
	while (node->rhs != NULL && node->rhs->kind != RE_DIRECTUIN)
	{
		len++;
		node = node->rhs;
	}
	return (len);
}

char	*exec_search_pash(const char *file, t_env_map *map)
{
	int		n;
	char	*path;
	char	*end_p;
	char	tmp_value[PATH_MAX];

	path = get_env(map, "PATH");
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
			return (strdup(tmp_value));
		bzero(tmp_value,PATH_MAX);
		path++;
		end_p = strchr(path, ':');
	}
	return (NULL);
}
