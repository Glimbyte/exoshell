/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:59:09 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/11 12:44:14 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_map		*map_new(void)
{
	t_env_map	*re;

	re = calloc(sizeof(t_env_map *), 1);
	if (re)
		fatal_error("cant malloc <env_map.c>");
	return (re);
}

char	*map_get(t_env_map *map, char *name)
{
	char	*re;
	t_env_item	*item;

	item = map->first_item;
	re = NULL;
	while (item != NULL)
	{
		if (strncmp(item->name, name, strlen(item->name)) == 0)
		{
			re = item->value;
			break ;
		}
		item = item->next;
	}
	return (re);
}

char	**get_full_env(t_env_map *map)
{
	char	**re;
	int		n;
	t_env_item	*item;

	item = map->first_item;
	re = calloc(sizeof(char *), map_len(map) + 1);
	n = 0;
	while (item)
	{
		if (item->value)
		{
			re[n] = ft_strjoin(item->name , "=");
			re[n] = ft_strjoin(re[n], item->value);
		}
		else
			re[n] = strdup(item->name);
		n++;
		item = item->next;
	}
	re[n] = 0;
	return (re);
}

int	map_len(t_env_map *map)
{
	int	n;
	t_env_item	*item;

	item = map->first_item;
	n = 0;
	while (item)
	{
		n++;
		item = item->next;
	}
	return (n);
}

t_env_map		*map_init(t_env_map *map, char **env)
{
	map->first_item = 0;
	while (*env)
	{
		map_put(map, *env);
		env++;
	}
	return (map);
}

int	map_put(t_env_map *map, char *string)
{
	char *equal;
	char *name;
	char *value;

	(void)map;
	equal = strchr(string, '=');
	if (equal == NULL)
	{
		name = strdup(string);
		value = NULL;
	}
	else
	{
		name = strndup(string, equal - string);
		value = strdup(equal + 1);
	}
	map_set(map, name, value);
	return (1);
}

t_env_item	*item_set(char *name, char *value)
{
	t_env_item	*new_item;

	new_item = calloc(sizeof(t_env_item), 1);
	new_item->name = name;
	new_item->value = value;
	new_item->next = NULL;
	return (new_item);
}


int	map_set(t_env_map *map, char *name, char *value)
{
	t_env_item	*tmp_item;

	tmp_item = map->first_item;
	if (name == NULL)
		return (0);
	if (value == NULL)
	{
		free (name);
		return (0);
	}
	if (tmp_item)
	{
		while (tmp_item->next)
			tmp_item = tmp_item->next;
		tmp_item->next = item_set(name, value);
	}
	else
		map->first_item = item_set(name, value);
	return (1);
}

int	map_unset(t_env_map *map, char *name)
{
	t_env_item	*item;
	t_env_item	*free_item;

	item = map->first_item;
	while (item->next != NULL)
	{
		if (strncmp(item->next->name, name, strlen(item->next->name)) == 0)
		{
			free_item = item->next;
			item->next = item->next->next;
			free(free_item->name);
			free(free_item->value);
			free(free_item);
			break ;
		}
		item = item->next;
	}
	if (item->next == NULL)
		return (0);
	return (1);
}

void	map_view(t_env_map *map)
{
	t_env_item *tmp;

	tmp = map->first_item;
	while (tmp)
	{
		printf ("---------------------------------------------\n");
		printf ("name	%s \n", tmp->name);
		printf ("value	%s \n", tmp->value);
		printf ("---------------------------------------------\n");
		tmp = tmp->next;
	}
}

char	*get_env(t_env_map *map, const char *name)
{
	t_env_item *item;

	item = map->first_item;
	while (strncmp(item->name, name, strlen(item->name)) != 0 && item->next != NULL)
		item = item->next;
	if (strncmp(item->name, name, strlen(item->name)) == 0)
		return (strdup(item->value));
	return (NULL);
}
