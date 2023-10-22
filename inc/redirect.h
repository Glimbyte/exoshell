/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 02:07:50 by mfujimak          #+#    #+#             */
/*   Updated: 2023/10/22 21:22:33 by mfujimak         ###   ########.fr       */
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

int	stashfd(int fd);
