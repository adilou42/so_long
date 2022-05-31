/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/31 18:57:36 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 1000)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int render_wall(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x <= 60 && y <= 60)
	{
		while (x <= 60 && y == 0)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->map.wall, x * 60, y);
			x++;
		}
		x = 1;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	// render_background(&data->img, 0xFFFFFF);
	// render_rect(&data->img, (t_rect){900, 400, 100, 100, 0x00FF00});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, 0xFF0000});

	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->map.floor, 0, 0);

	data->map.floor = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/floor.xpm", &data->map.height, &data->map.width);
	data->map.wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/wall.xpm", &data->map.height, &data->map.width);
	render_wall(data);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	printf("Move count: %d\n", data->count);
	data->count++;
	return (0);
}

int main(void)
{
	// 2 == C;
	// 3 == P;
	// 4 == E;
	char map[5][13] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,0,0,0,0,2,1},
		{1,0,0,0,0,1,1,1,1,1,0,0,1},
		{1,3,0,0,1,1,4,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int	x = 0;
	int	y;

	t_data	data;

	data.count = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		return (0);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 1200, "window of oufous");
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

	while (x < 5)
	{
		y = 0;
		while (y < 13)
		{
			if (map[x][y] == 1)
			{
				write(1, "1", 1);
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.wall, x * 60, y * 60);
			}
			else if (map[x][y] == 0)
			{
				write(1, "0", 1);

				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.floor, x * 60, y * 60);
			}
			else if (map[x][y] == 3)

			{
				write(1, "3", 1);

				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.player, x * 60, y * 60);
			}
			else if (map[x][y] == 2)
			{
				write(1, "2", 1);

				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.collectible, x * 60, y * 60);
			}
			else if (map[x][y] == 4)
			{
				write(1, "4", 1);

				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.map.exit, x * 60, y * 60);
			}
			y++;
		}
			write(1, "\n", 1);
		x++;
	}
	
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	// mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
