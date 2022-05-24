/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/24 21:02:13 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

void	render_background(t_data *data, int color)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return ;
	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 1000)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, color);
		++i;
	}
}

int render_rect(t_data *data, t_rect rect)
{
	int	i;
	int j;

	if (data->win_ptr == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{

	render_background(data, FFFFFF);
	render_rect(data, (t_rect){900, 400, 100, 100, 0xFF00});
	render_rect(data, (t_rect){0, 0, 100, 100, 0x00FF0000});

	return (0);
}

void	img_pixel_put(t_img *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_len + x * (image->bpp / 8));
	*(int *)pixel = color;
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
	t_img	image;

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

	image.mlx_img = mlx_new_image(data.mlx_ptr, 1000, 500);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
}
