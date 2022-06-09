/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:15:53 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 18:20:07 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	map_width(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] != '\n')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 && n-- - 1)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	hook(char **map, t_mlx mlx)
{
	t_world	world;

	world = create_world(map, &mlx);
	mlx_hook(world.mlx->win_ptr, 2, 1L << 0, deal_key, &world);
	mlx_hook(world.mlx->win_ptr, 17, 0L, exit_game, &world);
	mlx_loop_hook(world.mlx->mlx_ptr, refresh, &world);
	mlx_loop(world.mlx->mlx_ptr);
}
