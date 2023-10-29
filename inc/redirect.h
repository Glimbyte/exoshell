/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 02:07:50 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/25 17:13:50 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

typedef enum e_redirect_kind
{
	RK_IN,
	RK_OUT,
	RK_APPEND,
	RK_HEREDOC,
} t_redirect_kind;

typedef struct s_redirect t_redirect;
struct s_redirect
{
	char			*filename;
	t_redirect_kind	kind;
	int				fd;
	t_redirect		*next;
};

void	set_redirect(t_redirect *redir);
void	reset_redirect(t_redirect *redir);
void	prepare_redirect(int targetfd, t_redirect *redir);
void	close_redirect(int targetfd, t_redirect *redir);
int		open_redirect_fd(t_redirect *redir);

int	stashfd(int fd);

char *heredoc(char *delimiter);
