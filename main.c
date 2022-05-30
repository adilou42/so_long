/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/30 16:48:22 by ayakdi           ###   ########.fr       */
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

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	// render_background(&data->img, 0xFFFFFF);
	// render_rect(&data->img, (t_rect){900, 400, 100, 100, 0x00FF00});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, 0xFF0000});

	mlx_put_image_to_window(data->map.ptr, data->map.win, data->map.xpm, 1, 1);

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

	t_data	data;
	// t_world	map;

	data.count = 0;
	data.map.height = 17;
	data.map.width = 19;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		return (0);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1000, 500, "window of oufous");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (0);
	}

	// data.img.mlx_img = mlx_new_image(data.mlx_ptr, 1000, 500);
	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
	// 		&data.img.line_len, &data.img.endian);
	data.map.xpm = mlx_xpm_file_to_image(data.mlx_ptr, "./assets/floor.xpm", &data.map.height, &data.map.width);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	write(1, "BB\n", 3);

	mlx_loop(data.mlx_ptr);
	write(1, "AA\n", 3);

	mlx_destroy_display(data.win_ptr);
}
