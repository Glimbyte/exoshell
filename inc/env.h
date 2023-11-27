/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:50:51 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/27 13:47:43 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env_item t_env_item;
struct s_env_item
{
	char	*name;
	char	*value;
	t_env_item	*next;
};

typedef struct s_env_map t_env_map;
struct s_env_map
{
	t_env_item *first_item;
};

t_env_item		*item_new(char *name, char *value);
t_env_map		*map_new(void);
t_env_map		*map_init(t_env_map *map, char **env);
char			*map_get(t_env_map *map, char *name);
int				map_put(t_env_map *map, char *string);
int				map_set(t_env_map *map, char *name, char *value);
int				map_unset(t_env_map *map, char *name);
char			**get_env(t_env_map *map);
int				map_len(t_env_map *map);
void			map_view(t_env_map *map);
