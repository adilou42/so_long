/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:24:14 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/09 17:48:29 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_player	*create_player(int i, int j)
{
	t_player	*player;
	t_Coord		coord;

	player = (t_player *)malloc(sizeof(t_player));
	coord.y = i;
	coord.x = j;
	player->coord = coord;
	player->dir = -1;
	return (player);
}

void	player_move(t_world *world, int dir, int y, int x)
{
	printf("move count : %d\n", (++(world->move_count)));
	if (is_item(world->map[y][x]))
		world->item_count--;
	world->player->dir = dir;
	world->map[world->player->coord.y][world->player->coord.x] = '0';
	world->player->coord.y = y;
	world->player->coord.x = x;
	world->map[world->player->coord.y][world->player->coord.x] = 'P';
}

void	move(t_world *world, int dir)
{
	if (dir == 0 && is_accessible(world, world->map[world->player->coord.y - 1]
			[world->player->coord.x], world->player->coord.x,
			world->player->coord.y - 1))
		player_move(world, dir, world->player->coord.y - 1,
			world->player->coord.x);
	else if (dir == 1 && is_accessible(world,
			world->map[world->player->coord.y + 1][world->player->coord.x],
		world->player->coord.x, world->player->coord.y + 1))
		player_move(world, dir, world->player->coord.y + 1,
			world->player->coord.x);
	else if (dir == 2 && is_accessible(world, world->map[world->player->coord.y]
			[world->player->coord.x - 1],
			world->player->coord.x - 1, world->player->coord.y))
		player_move(world, dir, world->player->coord.y,
			world->player->coord.x - 1);
	else if (dir == 3 && is_accessible(world, world->map[world->player->coord.y]
			[world->player->coord.x + 1], world->player->coord.x + 1,
			world->player->coord.y))
		player_move(world, dir, world->player->coord.y,
			world->player->coord.x + 1);
	else
		return ;
}

t_world	create_world(char **map, t_mlx *mlx)
{
	int		i;
	int		j;
	t_world	world;

	i = 0;
	world.item_count = 0;
	while (map[i])
	{
		j = 0;
		while (is_mapset(map[i][j]))
		{
			if (map[i][j] == 'P')
				world.player = create_player(i, j);
			if (map[i][j] == 'C')
				world.item_count++;
			j++;
		}
		i++;
	}
	world.map = map;
	world.mlx = mlx;
	world.move_count = 0;
	stock_images(&world);
	return (world);
}
