/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/02 20:24:28 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"



char	*ft_strdup(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
		i++;
	res = malloc((i + 1) * sizeof (char));
	if (!res)
		return (0);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	lst_len(t_map *lmap)
{
	t_map	*tmp;
	int		i;

	if (!lmap)
		return (0);
	tmp = lmap;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**initialize_tmap(t_map *lmap)
{
	char	**tab;
	int		i;
	int		len;

	if (!lmap)
		return (0);
	len = lst_len(lmap);
	tab = (char **)malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = ft_strdup(lmap->line);
		if (!tab[i])
		{
			return (0);
		}
		i++;
		lmap = lmap->next;
	}
	tab[i] = NULL;
	// if (!verif_map(tab))
	// 	return (free_map(tab), NULL);
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

t_map	*parsing_map(int fd)
{
	char	*line;
	t_map	*lmap;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	lmap = creat_lmap_elem(line, len);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		push_last_elem(&lmap, line, ft_strlen(line));
	}
	
	return (lmap);
}

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == 97)//gauche
// 	{
// 		data->count++;
// 		printf("Move count: %d\n", data->count);
// 	}
// 	else if (keysym == 119)//haut
// 	{
// 		data->count++;
// 		printf("Move count: %d\n", data->count);
// 	}
// 	else if (keysym == 100)//droite
// 	{
		
// 		data->count++;
// 		printf("Move count: %d\n", data->count);
// 	}
// 	else if (keysym == 115)//bas
// 	{
// 		data->count++;
// 		printf("Move count: %d\n", data->count);

// 	}
// 	else if (keysym == XK_Escape)
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	return (0);
// }

void	init_images(t_world *world)
{
	write(1,"CC\n", 3);
	world->floor = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/floor.xpm", &world->height, &world->width);
	world->wall = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/wall.xpm", &world->height, &world->width);
	world->perso = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/player.xpm", &world->height, &world->width);
	world->collectible = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/collectible.xpm", &world->height, &world->width);
	world->exit = mlx_xpm_file_to_image(world->mlx->mlx_ptr, "./assets/exit.xpm", &world->height, &world->width);
	write(1, "DD\n", 3);
}

int	is_mapset(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'M'
		|| c == 'E' || c == 'P' || c == 'F')
		return (1);
	return (0);
}

t_player	*init_player(int i, int j)
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

t_world	init_world(char **map, t_mlx *mlx)
{
	int		i;
	int		j;
	t_world	world;

	i = 0;
	world.item_count = 0;
	while (map[i])
	{
		write(1, "AA\n", 3);
		j = 0;
		while (is_mapset(map[i][j]))
		{
			if (map[i][j] == 'P')
				world.player = init_player(i, j);
			if (map[i][j] == 'C')
				world.item_count++;
			j++;
		}
		i++;
	}
	write(1, "BB\n", 3);
	world.map = map;
	world.mlx = mlx;
	world.move_count = 0;
	init_images(&world);
	return (world);
}

void	affiche_elem(t_world world, int i, int j)
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
			affiche_elem(world, i, j);
			j++;
		}
		i++;
	}
}

int refresh(t_world *world)
{
	display_map(*world);
	return (1);
}

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
	// while (i < 3)
	// {
	// 	mlx_destroy_image(world->mlx->mlx_ptr, world->imgset[i].image);
	// 	i++;
	// }
	mlx_destroy_window(world->mlx->mlx_ptr, world->mlx->win_ptr);
	mlx_destroy_display(world->mlx->mlx_ptr);
	mlx_loop_end(world->mlx->mlx_ptr);
	free(world->mlx->mlx_ptr);
	exit(1);
}

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

int	deal_key(int key, t_world *world)
{
	// if (is_exit(*world)
	// 	&& world->map[world->player->coord.y][world->player->coord.x] == 'P')
	// {
	// 	if (key == 119)
	// 		move(world, 0);
	// 	else if (key == 115)
	// 		move(world, 1);
	// 	else if (key == 97)
	// 		move(world, 2);
	// 	else if (key == 100)
	// 		move(world, 3);
	// }
	if (key == 65307)
		free_world(world);
	return (1);
}

int main(int ac, char **av)
{
	(void)ac;
	t_mlx	mlx;
	t_world	world;
	t_map	*lmap;
	char	**map;
	int fd = open(av[1], O_RDONLY);

	lmap = parsing_map(fd);
	map = initialize_tmap(lmap);
	
	mlx.mlx_ptr = mlx_init();
	if (mlx.mlx_ptr == NULL)
	{
		return (0);
	}

	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 2500, 1000, "window of oufous");
	
	world = init_world(map, &mlx);
	mlx_hook(world.mlx->win_ptr, 2, 1L << 0, deal_key, &world);
	mlx_hook(world.mlx->win_ptr, 17, 0L, exit_game, &world);
	mlx_loop_hook(world.mlx->mlx_ptr, refresh, &world);

	mlx_loop(world.mlx->mlx_ptr);
	return (0);
}
