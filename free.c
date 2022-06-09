/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:22:32 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 19:32:41 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	free_world(t_world *world)
{
	int	i;

	i = 0;
	free_map(world->map);
	free(world->player);
	mlx_destroy_image(world->mlx->mlx_ptr, world->wall);
	mlx_destroy_image(world->mlx->mlx_ptr, world->floor);
	mlx_destroy_image(world->mlx->mlx_ptr, world->perso);
	mlx_destroy_image(world->mlx->mlx_ptr, world->collectible);
	mlx_destroy_image(world->mlx->mlx_ptr, world->exit);
	mlx_destroy_window(world->mlx->mlx_ptr, world->mlx->win_ptr);
	mlx_destroy_display(world->mlx->mlx_ptr);
	mlx_loop_end(world->mlx->mlx_ptr);
	free(world->mlx->mlx_ptr);
	exit(1);
}
