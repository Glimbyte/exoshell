/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:59:09 by mfujimak          #+#    #+#             */
/*   Updated: 2023/11/27 13:27:40 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_item	*item_new(char *name, char *value)
{
	t_env_item	*re;

	re = calloc(sizeof(t_env_item), 1);
	if (re == NULL)
		fatal_error("not calloc <env_map.c>");
	re->name = name;
	re->value = value;
	return (re);
}

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

char	**get_env(t_env_map *map)
{
	char	**re;
	int		n;
	t_env_item	*item;

	item = map->first_item;
	re = calloc(sizeof(char *), map_len(map));
	n = 0;
	while (item != NULL)
	{
		re[n] = strcat(item->name , "=");
		re[n] = strcat(re[n], item->value);
		n++;
		item = item->next;
	}
	return (re);
}

int	map_len(t_env_map *map)
{
	int	n;
	t_env_item	*item;

	item = map->first_item;
	n = 0;
	while (item != NULL)
	{
		n++;
		item = item->next;
	}
	return (n);
}

t_env_map		*map_init(char **env, t_env_map *map)
{
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

	equal = strchr(string, '=');
	if (equal == NULL)
	{
		name = strdup(string);
		value = NULL;
		if (name == NULL)
			fatal_error("not calloc <env_map.c>");
	}
	else
	{
		name = strndup(string, equal - string + 1);
		if (name == NULL)
			fatal_error("not calloc <env_map.c>");
		value = strdup(equal + 1);
		if (value == NULL)
			fatal_error("not calloc <env_map.c>");
	}
	map_set(map, name, value);
	return (1);
}

int	map_set(t_env_map *map, char *name, char *value)
{
	t_env_item	*item;

	item = map->first_item;
	while (item->next != NULL)
		item = item->next;
	item->next = item_new(name, value);
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
			item = item->next->next;
			free(free_item->name);
			free(free_item->value);
			free(free_item);
			break ;
		}
		item = item->next;
	}
	return (1);
}
