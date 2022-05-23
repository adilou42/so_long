/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakdi <ayakdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:59 by ayakdi            #+#    #+#             */
/*   Updated: 2022/05/23 19:37:44 by ayakdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	printf("Move count: %d\n", data->count);
	data->count++;
	// printf("Keypress: %d\n", keysym);
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

	data.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
}

// int main()
// {
// 	t_data	data;

// 	data->mlx_ptr = mlx_init();

// 	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 500, "window de oufous");
// 	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
// 	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
// 	mlx_loop(data->mlx_ptr);
// 	free(data->mlx_ptr);
// }