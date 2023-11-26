/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:50:51 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/26 18:35:57 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env_item t_env_item;
struct s_env_item
{
	char	*name;
	char	*value;
	t_item	*next;
};

typedef struct s_env_map t_env_map;
struct s_map
{
	t_env_item first_item;
};

t_env_item		*item_new(char *name, char *value);
t_env_map		*map_new(void);
t_env_map		*map_init(char **env, t_env_map *map);
char			*map_get(t_map *map, char *name);
int				map_put(t_map *map, char *string);
int				map_set(t_map *map, char *name, char *value);
int				map_unset(t_map *map, char *name);
char			**get_env(t_map *map);