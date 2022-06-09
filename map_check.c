/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 19:15:19 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 17:58:17 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	checkline(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	checkcol(char **col, int j)
{
	int	i;

	i = 0;
	while (col[i])
	{
		if (col[i][j] != '1' )
			return (0);
		i++;
	}
	return (1);
}

int	find_elem(char **map, char c)
{
	int	i;
	int	j;
	int	elem;

	i = 0;
	elem = 0;
	while (map[i])
	{
		j = 0;
		while (is_mapset(map[i][j]))
		{
			if (map[i][j] == c)
				elem++;
			j++;
		}
		i++;
	}
	if (!elem)
		return (0);
	return (elem);
}

int	check_wall(char **map, int height, int width)
{
	if (!checkline(map[0]) || !checkline(map[height - 1])
		|| !checkcol(map, 0) || !checkcol(map, width - 2))
		return (0);
	return (1);
}

int	check_rules(char **map, int height, int width)
{
	if (map == NULL)
		return (0);
	if (!check_wall(map, height, width))
		return (free_map(map), 0);
	if (!find_elem(map, 'E'))
	{
		return (free_map(map), 2);
	}
	else if (!find_elem(map, 'P'))
	{
		return (free_map(map), 3);
	}
	else if (!find_elem(map, 'C'))
	{
		return (free_map(map), 4);
	}
	return (1);
}
