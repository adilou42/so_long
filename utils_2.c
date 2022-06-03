/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:19:50 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/03 20:06:16 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_world *world)
{
	free_world(world);
	return (1);
}

int	is_exit(t_world world)
{
	int	i;
	int	j;

	i = 0;
	while (world.map[i])
	{
		j = 0;
		while (is_mapset(world.map[i][j]))
		{
			if (world.map[i][j] == 'F')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_mapset(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P' || c == 'F')
		return (1);
	return (0);
}

int	is_item(char c)
{
	if (c == 'C')
		return (1);
	return (0);
}