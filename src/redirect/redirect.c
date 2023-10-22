/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 02:07:13 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 20:22:07 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	prepare_redirect(int targetfd, t_redirect *redir)
{
	int	filefd;
	int	stashed_targetfd;

	filefd = open_redirect_fd(redir);
	stashfd(filefd);
	stashed_targetfd = stashfd(targetfd);
	if (filefd != targetfd)
	{
		dup2(filefd, targetfd);
		close(filefd);
	}
	redir->fd = stashed_targetfd;
}

void	close_redirect(int targetfd, t_redirect *redir)
{
	dup2(redir->fd, targetfd);
}

int	open_redirect_fd(t_redirect *redir)
{
	int fd;

	if (redir->kind == RK_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->kind == RK_OUT)
		fd = open(redir->filename, O_WRONLY);
	else if (redir->kind == RK_APPEND)
		fd = open(redir->filename, O_APPEND);
	else if (redir->kind == RK_HEREDOC)
		Todo("dont open heredoc <redirect.c>");
	return (fd);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}
