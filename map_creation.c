/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 17:38:27 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/03 20:36:31 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	verif_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j])
		{
			if (!is_mapset(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**initialize_tmap(t_map *lmap)
{
	char	**tab;
	int		i;
	int		len;

	if (!lmap)
		print_error(NULL);
	len = lst_len(lmap);
	tab = (char **)malloc((len + 1000) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = ft_strdup(lmap->line);
		if (!tab[i])
		{
			return (free_map(tab), NULL);
		}
		i++;
		lmap = lmap->next;
	}
	tab[i] = NULL;
	if (!verif_map(tab))
		return (free_map(tab), NULL);
	return (tab);
}

t_map	*creat_lmap_elem(char *line, size_t len)
{
	t_map	*tmp;

	tmp = (t_map *)malloc(sizeof(t_map));
	if (!tmp)
		return (NULL);
	tmp->line = line;
	tmp->len = len;
	tmp->next = NULL;
	return (tmp);
}

int	push_last_elem(t_map **lmap, char *line, size_t len)
{	
	t_map	*tmp;
	t_map	*elem;

	tmp = NULL;
	if (!lmap)
		return (0);
	elem = creat_lmap_elem(line, len);
	if (!(*lmap))
		*lmap = elem;
	else
	{
		tmp = *lmap;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	return (1);
}

void	display_map(t_world world)
{
	int		i;
	int		j;
	// char	*nb_moves;

	i = 0;
	j = 0;
	while (world.map[i])
	{
		j = 0;
		while (is_mapset(world.map[i][j]))
		{
			display_elem(world, i, j);
			j++;
		}
		i++;
	}
	// nb_moves = ft_itoa(world.move_count);
}