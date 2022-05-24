/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/24 15:53:45 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	printf("Move count: %d\n", data->count);
	data->count++;
	return (0);
}

int	handle_keyrelease(void	*data)
{
	(void)data;
	return (0);
}

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int main(void)
{

	t_data	data;
	t_map	img;

	data.count = 0;
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

	img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img.img, 0, 0);


	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
}
