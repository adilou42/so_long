/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/06 19:33:06 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stock_images(t_world *world)
{
	world->floor = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/floor.xpm", &world->height, &world->width);
	world->wall = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/wall.xpm", &world->height, &world->width);
	world->perso = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/player.xpm", &world->height, &world->width);
	world->collectible = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/collectible.xpm", &world->height, &world->width);
	world->exit = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/exit.xpm", &world->height, &world->width);
}

void	display_elem(t_world world, int i, int j)
{
	if (world.map[i][j] == '0')
	{
		mlx_put_image_to_window(world.mlx->mlx_ptr, 
			world.mlx->win_ptr, world.floor, j * 60, i * 60);
	}
	else if(world.map[i][j] == '1')
	{
		mlx_put_image_to_window(world.mlx->mlx_ptr, 
			world.mlx->win_ptr, world.wall, j * 60, i * 60);
	}
	else if (world.map[i][j] == 'C')
	{
		mlx_put_image_to_window(world.mlx->mlx_ptr, 
			world.mlx->win_ptr, world.collectible, j * 60, i * 60);
	}
	else if (world.map[i][j] == 'E')
	{
		mlx_put_image_to_window(world.mlx->mlx_ptr, 
			world.mlx->win_ptr, world.exit, j * 60, i * 60);
	}
	else if (world.map[i][j] == 'P')
	{
		mlx_put_image_to_window(world.mlx->mlx_ptr, 
			world.mlx->win_ptr, world.perso, j * 60, i * 60);
	}
}

int refresh(t_world *world)
{
	usleep(20000);
	display_map(*world);
	world->player->dir = -1;

	return (1);
}

int	deal_key(int key, t_world *world)
{
	if (is_exit(*world)
		&& world->map[world->player->coord.y][world->player->coord.x] == 'P')
	{
		if (key == 119) //haut
			move(world, 0);
		else if (key == 115) //bas
			move(world, 1);
		else if (key == 97)  //gauche
			move(world, 2);
		else if (key == 100) //droite
			move(world, 3);
	}
	if (key == 65307)
		free_world(world);
	return (1);
}


int map_height(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
	{
		i++;
	}
	printf("i = %d\n", i);
	return (i);
}
int map_width(char **map)
{
	int i;

	i = 0;
	while (map[0][i] != '\n')
	{
		i++;
	}
	printf("i = %d\n", i);
	return (i);
}

int main(int ac, char **av)
{
	t_mlx	mlx;
	t_world	world;
	t_map	*lmap;
	char	**map;

	if (ac != 2)
	{
		write(1, "BB\n", 3);
		// return (0);
		exit(EXIT_FAILURE);
	}
	int fd = open(av[1], O_RDONLY);

	lmap = parsing_map(fd);
	map = initialize_tmap(lmap);
	if (!check_rules(map, lst_len(lmap), lmap->len))
		print_error(lmap);
	ft_lstclear(&lmap);
	
	mlx.mlx_ptr = mlx_init();
	if (!(mlx.mlx_ptr))
	{
		print_mlx_error(map);
	}

	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, map_width(map) * 60, map_height(map) * 60, "window of oufous");
	
	world = create_world(map, &mlx);
	mlx_hook(world.mlx->win_ptr, 2, 1L << 0, deal_key, &world);
	mlx_hook(world.mlx->win_ptr, 17, 0L, exit_game, &world);
	mlx_loop_hook(world.mlx->mlx_ptr, refresh, &world);

	mlx_loop(world.mlx->mlx_ptr);
	return (0);
}
