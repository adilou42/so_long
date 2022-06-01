/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/06/01 18:59:55 by ayakdi           ###   ########.fr       */
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

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 97)//gauche
	{
		data->count++;
		printf("Move count: %d\n", data->count);
	}
	else if (keysym == 119)//haut
	{
		data->count++;
		printf("Move count: %d\n", data->count);
	}
	else if (keysym == 100)//droite
	{
		
		data->count++;
		printf("Move count: %d\n", data->count);
	}
	else if (keysym == 115)//bas
	{
		data->count++;
		printf("Move count: %d\n", data->count);

	}
	else if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	t_data	data;
	// t_player	player;
	t_map	*lmap;
	char	**map;
	int fd = open(av[1], O_RDONLY);

	lmap = parsing_map(fd);
	map = initialize_tmap(lmap);

	// char map[5][13] = {
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,1,0,0,0,0,0,0,0,'C',1},
	// 	{1,0,0,0,0,1,1,1,1,1,0,0,1},
	// 	{1,'P',0,0,1,1,'E',0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };

	// int	x = 0;
	// int	y;


	data.count = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		return (0);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 13 * 60, 5 * 60, "window of oufous");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (0);
	}
	data.map.floor = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/floor.xpm", &data.map.height, &data.map.width);
	data.map.wall = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/wall.xpm", &data.map.height, &data.map.width);
	data.map.player = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/player.xpm", &data.map.height, &data.map.width);
	data.map.collectible = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/collectible.xpm", &data.map.height, &data.map.width);
	data.map.exit = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/exit.xpm", &data.map.height, &data.map.width);

	// while (x < 5)
	// {
	// 	y = 0;
	// 	while (y < 13)
	// 	{
	// 		if (map[x][y] == 1)
	// 		{
	// 			write(1, "1", 1);
	// 			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.wall, y * 60, x * 60);
	// 		}
	// 		else if (map[x][y] == 0)
	// 		{
	// 			write(1, "0", 1);

	// 			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.floor, y * 60, x * 60);
	// 		}
	// 		else if (map[x][y] == 'P')

	// 		{
	// 			write(1, "P", 1);
	// 			player.x = x;
	// 			player.y = y;
	// 			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.player, y * 60, x * 60);
	// 		}
	// 		else if (map[x][y] == 'C')
	// 		{
	// 			write(1, "C", 1);

	// 			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.collectible, y * 60, x * 60);
	// 		}
	// 		else if (map[x][y] == 'E')
	// 		{
	// 			write(1, "E", 1);

	// 			mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.exit, y * 60, x * 60);
	// 		}
	// 		y++;
	// 	}
	// 		write(1, "\n", 1);
	// 	x++;
	// }
	
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
